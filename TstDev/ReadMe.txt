This is a new BDA interface wrapper for AltDVB v2.2.

The configuration file (Dev_Bda2Driver.cfg) should be placed in the same folder
as the interface (Dev_Bda2Driver.int). If this file doesn't exist, the interface driver
will create a new one with default values.

S2 Pilot and S2 Roll Off:
these values are for the Haupppauge drivers and practically should not be changed

v 0.2.0.21 - 2013.07.31 - CrazyCat
- Fix Pinnacle 4xxe support (Technotrend BDA).

v 0.2.0.20 - 2013.02.05 - CrazyCat
- Fix DVBWorld BDA-extension support (DiSEqC 1.x).

v 0.2.0.19 - 2012.11.24 - CrazyCat
- Netup BDA-extension support (DiSEqC 1.x).
- Fix Genpix BDA-extension support (ToneBurst, DiSEqC 1.x).

v 0.2.0.18 - 2012.05.07 - CrazyCat
- Fix Bestunar/DVBSky BDA-extension support (DiSEqC 1.x).

v 0.2.0.17 - 2012.04.07 - CrazyCat
- Fix Compro BDA-extension support (DiSEqC 1.x).

v 0.2.0.16 - 2011.12.25 - CrazyCat
- Genpix BDA-extension support (ToneBurst, DiSEqC 1.x).
- Genpix 3dparty BDA-extension support (ToneBurst. DiSEqC 1.x).
- Compro BDA-extension support (DiSEqC 1.x, LNB power control).
- AnySee BDA-extension support (Toneburst, DiSEqC 1.x control).
- DVBWorld support improved.
----------

v 0.2.0.15 - 2011.12.01 - CrazyCat
- Bestunar/DVBSky BDA-extension support (DiSEqC 1.x control).
- Improved Omicom, TeVii BDA-extension support.
----------

v 0.2.0.14 - 2011.11.01 - CrazyCat
- TBS QBox detection fix. QBox BDA-extension preffered except Prof 7500.
----------

v 0.2.0.13 - 2011.08.03 - CrazyCat
- New option - Relock after timeout. Useful for motorized dishes or periodical signal drops.
----------

v 0.2.0.12 - 2011.07.25 - CrazyCat
- Fix modulation autodetect.
- 8VSB modulation for satellite devices used as NBC_QPSK
----------

v 0.2.0.11 - 2011.06.21 - CrazyCat
- Device configuration dialog implemented.
----------

v 0.2.0.10 - 2011.05.29 - CrazyCat
- Continous 22Khz tone control, when LOF Switch=0.
- Turbosight 6925 V2 support (DiSEqC 1.x control).
- Turbosight QBOXs support fixed again (DiSEqC 1.x control).
----------

v 0.2.0.9 - 2011.01.30 - CrazyCat
- Turbosight QBOXs (and ODM like Prof 1100, MatchBox Pro) support fixed (DiSEqC 1.x, LNB power control).
----------

v 0.2.0.8 - 2010.10.09 - CrazyCat
- Revert 0.2.0.7 changes (LNB power-on failed for some devices).
- Omicom S2 DiSEqC 1.x minor fix (enable continous 22Khz (50ms) before DiSEqC command).
- Turbosight QBOX, QBOX2, QBOX-S2 and Prof 1100 support (DiSEqC 1.x, LNB power control).
----------

v 0.2.0.7 - 2010.09.28 - CrazyCat
- Initial DVB-S tuning speed-up.
----------

v 0.2.0.6 - 2010.09.04 - CrazyCat
- Initial DVB-S tuning again fixed (power-on).
----------

v 0.2.0.5 - 2010.08.01 - CrazyCat
- Experimental Microsoft Windows7 DiSEqC BDA-extension support. Used in Windows7 Media Center (DiSEqC 1.0), if driver provide this extension.
  Most Win7-designed BDA-drivers provide this extension only for DiSEqC 1.0, but specification support RAW DiseqC 1.x/2.x and ToneBurst.
  Current build support only ToneBurst/DiSEqC 1.0 for this extension (but in sources implemented also RAW DiseqC support).
- New configuration file option BDA_TYPE - preffered BDA-extension (Microsoft or TeVii). BDA extension always autodetected and this option can change priority.
----------

v 0.2.0.4 - 2010.07.25 - CrazyCat
- Initial DVB-S tuning fixed (power-on, power-off).
----------

v 0.2.0.3 - 2010.07.18 - CrazyCat
- DVB-S tuning code cleanup.
----------

v 0.2.0.2 - 2010.07.04 - CrazyCat
- Change BDA type detection order. Use Turbosight, DVBWorld extension for TeVii devices with old drivers (pre 2009).
- Show Technotrend product name instead tuner filter name.
- Change credits and added project url in device selection dialog.
----------

v 0.2.0.1 - 2010.06.24 - CrazyCat
- Removed DVBS2Signalling, DiSEqC, S_ROLLOFF settings from config.
- Added FEC support.
- LNB power-off support.
- Vendor-specific BDA extension autodetection. Now supported:
	* Technotrend BDA API (use ttBdaDrvApi_Dll.dll). ToneBurst + Raw DiSEqC, LNB power-off, Modulation type selection.
	* Hauppauge BDA extension. Raw DiSEqC, Modulation type selection, S2 Pilot/RollOff settings.
	* Conexant BDA extension. Raw DiSEqC, Modulation type selection, S2 Pilot/RollOff settings (optional), LNB power-off (optional).
	* DvbWorld BDA extension. ToneBurst + Raw DiSEqC, Modulation type selection.		
	* Turbosight BDA extension. Raw DiSEqC, Modulation type selection, LNB power-off.
	* Twinhan BDA extension. ToneBurst + Raw DiSEqC, Modulation type selection, LNB power-off.
	* TeVii BDA API (TeVii.dll). Raw DiSEqC, LNB power-off, Modulation type selection.	
	* Omicom BDA extension. Raw DiSEqC, Modulation type selection.
----------

v 0.1.0.12 - 2010.06.17 - CrazyCat
- recompiled with latest Technotrend BDA SDK (1.0.1.21). Now use ttBdaDrvApi_Dll.dll
- now on Google Code - http://code.google.com/p/altbda2
----------

v 0.1.0.11 - 2008.01.28
----------

- new implementation of raw DiSEqC support for Technotrend budget
  DiSEqC works only with Technotrend BDA drivers v.4.4.10.x and v5.0.0.12
- Hauppauge DVB-S2 tuning still in beta phase

v 0.1.0.10 beta1 - 2008.01.25
----------

- added support for Hauppauge proprietary interface (8PSK tuning
  and DiSEqC)
- Hauppauge DiSEqC has been fixed.
 
v 0.1.0.9
---------
- private TT DiSEqC test release

---------
v 0.1.0.8 - 2007.11.24
---------

- fixed tuning for Airstar-2 with final BDA 4.4.1 drivers
- removed "failed put_FrequencyMultiplier" message, most drivers don't implement it

v 0.1.0.7 - 2007.11.20
---------

- fixed bug when tuner reports signal statistics on more than one topology node

v 0.1.0.6 - 2007.11.19
---------

-code cleanup

v 0.1.0.4 - 2007.11.15
---------

- fixed bug for TwinHan AD-SP400 CI
- fixed bug for DVB-C Twinhan 2033 Mantis
- fixed bug in put_Range introduced in a private release
- code cleanup

v 0.1.0.2 - 2007.11.14
---------

- fixed bug for KNC One
- added configuration file
  a) those that can't tune to DVB-S2 channels try changing the default 8VSB
     to 8PSK value - newer drivers use new value for 8PSK signalling
  b) DiSEqC configuration for now is always COMMITED

v 0.1.0.1 - 2007.11.12
---------

- fixed bug when there is no seperate Capture filter
- fixed bug with hard-coded LowBandF, HighBandF, SwitchF for DVB-S tuning
- added more error logging
- tweaked tuning


v 0.1.0.0 - 2007.11.09
---------

A few weeks ago I have decided to try to write an alternative BDA device interface
for AltDVB v2.2.0 build 3912 for my TT S2-3200 card with v5.0.0.x BDA drivers.
It might work with other BDA compatible devices (DVB-S/T/C), but no guarantee is given.

1) please don't ask me for the device interface SDK for AltDVB v2.2 since I
   simply don't have it (the knowledge to write this implementation was gathered
   just by observing when and which information is exchanged between the main
   application and the original Dev_BdaDriver.int)
   - I might release in the future my knowledge on the device interface
   - if AltX wishes that this information shall not ever be disclosed I will honor
     his decision
   - no, I am not in any contact with AltX, nor know his whereabouts
     (wish him all the best though :)

2) it might work with other BDA compatible devices, but no guarantee is given

3) Technotrend's BDA drivers (still) have difficulties with DiSEqC 1.0 under BDA,
   especially when tuning to 8PSK transponders

4) DVB-S support has been tested only with the TT S2-3200 card (aka SkystarHD)

5) DVB-T support has been tested only with the TwinHan MagicBox Pro VP-704A
   (aka Pinnacle PCTV-310e)

6) don't have access to DVB-C hardware, so it's not tested at all

7) if you want to report an anomaly/bug/strange behavior please be specific, provide
   as much information as possible about your configuration/ devices etc and
   the log from http://www.microsoft.com/technet/sysinternals/utilities/debugview.mspx
   I will try, if my free time permits, to look into the problem

8) CI & IR remote will probably not ever be supported

Parts of my work are based on the work of DCoder, nate et al from the
the DVB Owners Discussion Forum. Good work guys! Cheers.

Diodato
