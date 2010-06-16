#include "stdafx.h"

#include "DvbDeviceControl.h"

CDvbDeviceControl::CDvbDeviceControl(HMODULE hModule)
{
	hInstance = hModule;
	stream_callback = NULL;
	selected_device_enum = 0;
	message_callback = NULL;
	ConfigurationFileExists = FALSE;
	conf_params.ConfVer[0] = 0x0;
	conf_params.ConfMod8PSK = DEFAULT_MOD_8PSK;
	conf_params.ConfDiSEqC = DEFAULT_DISEQC;
}

CDvbDeviceControl::~CDvbDeviceControl()
{
}

int CDvbDeviceControl::DriverDescription(struct DRIVER_DATA *d)
{
	sprintf(d->author,"Diodato");
	sprintf(d->description,"BDA DVB-S/T/C Interface");
	sprintf(d->url,"");

	return AltxDVB_OK;
}

int CDvbDeviceControl::DeviceDescription(struct DEVICE_DATA *d)
{
	struct NetworkTuners Tuners;

	BdaGraph.GetNetworkTuners(&Tuners);
	d->dev_cnt = Tuners.Count;

	for(int i=0; i<Tuners.Count; ++i)
	{
		if(IsEqualGUID(Tuners.Tuner[i].Type, CLSID_DVBSNetworkProvider))
			d->device[i].dev_type = (DEVICE_TYPE)(DVBS | (Tuners.Tuner[i].Availability ? AVAILABLE : 0x0));
		else
		if(IsEqualGUID(Tuners.Tuner[i].Type, CLSID_DVBTNetworkProvider))
			d->device[i].dev_type = (DEVICE_TYPE)(DVBT | (Tuners.Tuner[i].Availability ? AVAILABLE : 0x0));
		else
		if(IsEqualGUID(Tuners.Tuner[i].Type, CLSID_DVBCNetworkProvider))
			d->device[i].dev_type = (DEVICE_TYPE)(DVBC | (Tuners.Tuner[i].Availability ? AVAILABLE : 0x0));
		else
			d->device[i].dev_type = (DEVICE_TYPE)ERR;

		strcpy(d->device[i].dev_name, Tuners.Tuner[i].Name);
		sprintf(d->device[i].dev_id, "%d", Tuners.Tuner[i].Id);
	}

	return AltxDVB_OK;
}

int CDvbDeviceControl::MessageCallback(MSG_CB_PROC d)
{

	message_callback = d;
	BdaGraph.MessageCallback(d);

	return AltxDVB_OK;
}

int CDvbDeviceControl::OpenDevice(struct OPEN_DEVICE_DATA *d)
{
	if(sscanf(d->dev_id,"%d",&selected_device_enum) != 1)
		return AltxDVB_ERR;
	selected_device_type = (DEVICE_TYPE)(d->dev_type);
	if(SUCCEEDED(BdaGraph.BuildGraph(selected_device_enum, (enum VENDOR_SPECIFIC *)&(conf_params.VendorSpecific))))
	{
		char selected_device_name[128];

		WideCharToMultiByte(CP_ACP, 0, BdaGraph.friendly_name_tuner, -1, selected_device_name, sizeof(selected_device_name), NULL, NULL);
		Configure(hInstance, selected_device_enum, selected_device_name);
		if(SUCCEEDED(BdaGraph.RunGraph()))
			return AltxDVB_OK;
		else
			BdaGraph.CloseGraph();
	}
	else
		BdaGraph.CloseGraph();

	return AltxDVB_ERR; // non 0x0 quits AltDVB
}

int CDvbDeviceControl::CloseDevice(int *d)
{
	BdaGraph.CloseGraph();
	VendorSpecificClose();

	return AltxDVB_OK;
}

int CDvbDeviceControl::DeviceName(struct DEVICE_NAME_DATA *d)
{
	char txt[121];

	if(selected_device_enum == 0x0)
		return AltxDVB_ERR;
	WideCharToMultiByte(CP_ACP, 0, BdaGraph.friendly_name_tuner, -1, txt, sizeof(txt), NULL, NULL);
	sprintf(d->description,"BDA2 [%s]",txt);
	return AltxDVB_OK;
}

int CDvbDeviceControl::PidFilter(struct PID_FILTER_DATA *d)
{
	return AltxDVB_OK; // d->pid == 0x2000 means all PIDs
}

int CDvbDeviceControl::StreamCallback(STR_CB_PROC d)
{
	stream_callback = d;
	BdaGraph.SetStreamCallbackProcedure(d);

	return AltxDVB_OK; // 0x0 OK, non zero quits AltDVB
}

int CDvbDeviceControl::Tune(struct TUNE_DATA *d)
{
	SpectralInversion SpectrInv;
	ModulationType ModType;
	LONG PosOpt;
	Polarisation Pol;

	switch(selected_device_type)
	{
	case DVBS:
		/* first tuning? */
		if(d->polarity == LNB_POWER_ON)
		{
			switch(conf_params.VendorSpecific)
			{
			case PURE_BDA:
			if(FAILED(BdaGraph.DVBS_Tune(
					(ULONG)(DEFAULT_LOW_OSCILLATOR),
					(ULONG)(DEFAULT_HIGH_OSCILLATOR),
					(ULONG)(DEFAULT_LNB_SWITCH),
					(ULONG)(DEFAULT_FREQUENCY_S),
					DEFAULT_INVERSION_S,
					DEFAULT_MODULATION_S,
					(LONG)(DEFAULT_SYMBOLRATE_S),
					DEFAULT_POS_OPT,
					DEFAULT_POLARISATION)))
				return AltxDVB_ERR;
				break;
			case TT_BDA:
			if(FAILED(BdaGraph.DVBS_TT_Tune(
					(ULONG)(DEFAULT_LOW_OSCILLATOR),
					(ULONG)(DEFAULT_HIGH_OSCILLATOR),
					(ULONG)(DEFAULT_LNB_SWITCH),
					(ULONG)(DEFAULT_FREQUENCY_S),
					DEFAULT_INVERSION_S,
					DEFAULT_MODULATION_S,
					(LONG)(DEFAULT_SYMBOLRATE_S),
					DEFAULT_POLARISATION)))
				return AltxDVB_ERR;
				break;
			case HAUP_BDA:
			if(FAILED(BdaGraph.DVBS_Hauppauge_Tune(
					(ULONG)(DEFAULT_LOW_OSCILLATOR),
					(ULONG)(DEFAULT_HIGH_OSCILLATOR),
					(ULONG)(DEFAULT_LNB_SWITCH),
					(ULONG)(DEFAULT_FREQUENCY_S),
					DEFAULT_INVERSION_S,
					DEFAULT_MODULATION_S,
					(LONG)(DEFAULT_SYMBOLRATE_S),
					DEFAULT_POS_OPT,
					DEFAULT_POLARISATION,
					conf_params.RollOff,
					conf_params.S2RollOff,
					conf_params.S2Pilot,
					conf_params.ConfDiSEqC == DISEQC_RAW)))
				return AltxDVB_ERR;
				break;
			}
			return AltxDVB_OK;
		}
		/* LNB power off - can BDA handle this? */
		if(d->polarity == LNB_POWER_OFF)
			return AltxDVB_OK;
		/* not first tuning */
		switch(d->inversion)
		{
			case INV_AUTO:	SpectrInv = BDA_SPECTRAL_INVERSION_AUTOMATIC; break;
			case INV_OFF:	SpectrInv = BDA_SPECTRAL_INVERSION_NORMAL; break;
			case INV_ON:	SpectrInv = BDA_SPECTRAL_INVERSION_INVERTED; break;
			default: SpectrInv = BDA_SPECTRAL_INVERSION_NOT_DEFINED;
		};
		switch(d->polarity)
		{
			case LNB_POWER_OFF:		Pol = BDA_POLARISATION_NOT_DEFINED; break;
			case LNB_POWER_ON:		Pol = BDA_POLARISATION_LINEAR_V; break;
			case LINEAR_HORIZONTAL:	Pol = BDA_POLARISATION_LINEAR_H; break;
			case LINEAR_VERTICAL:	Pol = BDA_POLARISATION_LINEAR_V; break;
			default: Pol = BDA_POLARISATION_NOT_SET;
		};
		switch(d->modulation)
		{
			case MOD_AUTO:	ModType = BDA_MOD_NOT_DEFINED; break;
			case MOD_QPSK:	ModType = BDA_MOD_QPSK; break;
			case MOD_8PSK:	ModType = conf_params.ConfMod8PSK; break;
			default: ModType = BDA_MOD_QPSK;
		};
		switch(d->switches)
		{
			case POS_A_OPT_A: PosOpt=0x000; break;
			case POS_B_OPT_A: PosOpt=0x001; break;
			case POS_A_OPT_B: PosOpt=0x100; break;
			case POS_B_OPT_B: PosOpt=0x101; break;
			case SW_NONE: PosOpt=0xffffffff; break;
			default: PosOpt=0xffffffff; break;
		}
		switch(conf_params.VendorSpecific)
		{
		case PURE_BDA:
			if(FAILED(BdaGraph.DVBS_Tune(
				(ULONG)(d->lnb_low),
				(ULONG)(d->lnb_high),
				(ULONG)(d->lnb_switch),
				(ULONG)(d->frequency),
				SpectrInv,
				ModType,
				(LONG)(d->symbol_rate),
				PosOpt,
				Pol)))
				return E_FAIL;
			break;
		case HAUP_BDA:
			if(FAILED(BdaGraph.DVBS_Hauppauge_Tune(
					(ULONG)(d->lnb_low),
					(ULONG)(d->lnb_high),
					(ULONG)(d->lnb_switch),
					(ULONG)(d->frequency),
					SpectrInv,
					ModType,
					(LONG)(d->symbol_rate),
					PosOpt,
					Pol,
					conf_params.RollOff,
					conf_params.S2RollOff,
					conf_params.S2Pilot,
					conf_params.ConfDiSEqC == DISEQC_RAW)))
				return AltxDVB_ERR;
			break;
		case TT_BDA:
			if(FAILED(BdaGraph.DVBS_TT_Tune(
				(ULONG)(d->lnb_low),
				(ULONG)(d->lnb_high),
				(ULONG)(d->lnb_switch),
				(ULONG)(d->frequency),
				SpectrInv,
				ModType,
				(LONG)(d->symbol_rate),
				Pol)))
				return AltxDVB_ERR;
			break;
		}
		break;
	case DVBT:
		if(FAILED(BdaGraph.DVBT_Tune(
				(ULONG)(d->frequency),
				(ULONG)(d->bandwidth))))
			return AltxDVB_ERR;
		break;
	case DVBC:
		switch(d->modulation)
		{
			case MOD_AUTO:		ModType = BDA_MOD_NOT_SET; break;
			case MOD_QAM_16:	ModType = BDA_MOD_16QAM; break;
			case MOD_QAM_32:	ModType = BDA_MOD_32QAM; break;
			case MOD_QAM_64:	ModType = BDA_MOD_64QAM; break;
			case MOD_QAM_128:	ModType = BDA_MOD_128QAM; break;
			case MOD_QAM_256:	ModType = BDA_MOD_256QAM; break;
			default: ModType = BDA_MOD_NOT_SET;
		};
		if(FAILED(BdaGraph.DVBC_Tune(
				(ULONG)(d->frequency),
				(LONG)(d->symbol_rate),
				ModType)))
			return AltxDVB_ERR;
		break;
	}
	return AltxDVB_OK;
}

int CDvbDeviceControl::SignalStatistics(struct SIGNAL_STATISTICS_DATA *d)
{
	HRESULT hr;
	BOOLEAN present=FALSE,locked=FALSE;
	LONG strength=0, quality=0;

	d->quality = 0;
	d->strength = 0;
	d->flags = 0x0;
	hr = BdaGraph.GetSignalStatistics(&present,&locked,&strength,&quality);
	if(SUCCEEDED(hr))
	{
		d->flags = (locked? 0x10 : 0x00) | (present? 0x0F : 0x00);
		d->strength = (int)strength;
		d->quality = (int)quality;
		return AltxDVB_OK;
	}
	return AltxDVB_ERR;
}

int CDvbDeviceControl::DiSEqC_Command(struct DISEQC_COMMAND_DATA *d)
{
	char txt[256];
	sprintf(txt,"DiSEqC len=%d",d->len);
	DebugLog(txt);
	for(int i=0;i<d->len;++i)
	{
	sprintf(txt,"DiSEqC %2.2x",d->DiSEqC_Command[i]);
	DebugLog(txt);
	}
	switch(conf_params.VendorSpecific)
	{
	case PURE_BDA: return AltxDVB_ERR;
	case TT_BDA:
		if(VendorSpecificDiSEqC(d->len, d->DiSEqC_Command))
			return AltxDVB_ERR;
		break;
	case HAUP_BDA:
		if(BdaGraph.DVBS_Hauppauge_DiSEqC(d->len, d->DiSEqC_Command))
			return AltxDVB_ERR;
		break;
	}
	return AltxDVB_OK;
}

int CDvbDeviceControl::DiSEqC_Support(struct DISEQC_SUPPORT_DATA *d)
{
	d->DiSEqC_Support = (enum DISEQC_TYPE)conf_params.ConfDiSEqC;

	return AltxDVB_OK;
}

int CDvbDeviceControl::DeviceConfig(void)
{
	if(DoConfigurationDialog())
		return AltxDVB_OK;
	else
		return AltxDVB_ERR;
}

int CDvbDeviceControl::DeviceOpensWholeTransponder(struct WHOLE_TRANSPONDER_DATA *d)
{
	d->OpensWholeTransponder = 0x1; // 0x1 - device can open whle transponder, 0x0 - no it cannot
	return AltxDVB_OK;
}

