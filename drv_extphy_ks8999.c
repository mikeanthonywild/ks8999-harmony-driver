/*******************************************************************************
  Micrel KS8999 PHY API for Microchip TCP/IP Stack
*******************************************************************************/

/*******************************************************************************
File Name:  drv_extphy_ks8999.c
*******************************************************************************/
#include "driver/ethphy/src/dynamic/drv_extphy.h"

#include "system_config.h"

/****************************************************************************
 *                 interface functions
 ****************************************************************************/


/****************************************************************************
 * Function:        DRV_EXTPHY_MIIConfigure
 *
 * PreCondition:    - Communication to the PHY should have been established.
 *
 * Input:   		handle - A valid open-instance handle, returned from the driver's open routine
 *					cFlags - the requested configuration flags: ETH_PHY_CFG_RMII/ETH_PHY_CFG_MII
 *
 * Output:          ETH_RES_OK - operation completed successfully
 *
 *                  ETH_RES_PENDING - operation pending; the call needs to be re-issued until
 *                                    ETH_RES_OK or an error reported
 *
 *
 *                  < 0         - an error occurred and the operation was aborted
 *
 * Side Effects:    None
 *
 * Overview:        This function configures the PHY in one of MII/RMII operation modes.
 *
 *****************************************************************************/
ETH_RESULT_CODE DRV_EXTPHY_MIIConfigure(DRV_HANDLE hClientObj,ETHPHY_CONFIG_FLAGS cFlags)
{
    /*
    union
    {
        struct
        {
            uint16_t low;
            uint16_t high;
        };
        uint32_t    w;
    }vendorData;

    uint16_t    phyReg;
    uint16_t    miiConfPhase;
    int         phyAddress;

    ETH_RESULT_CODE res = DRV_ETHPHY_VendorDataGet(hClientObj, &vendorData.w);

    if(res < 0)
    {   // some error occurred
        return res;
    }

    miiConfPhase = vendorData.low;

    DRV_ETHPHY_PhyAddressGet(hClientObj, &phyAddress);

    switch(miiConfPhase)
    {
        case 0:
            res = DRV_ETHPHY_VendorSMIReadStart(hClientObj, PHY_REG_SPECIAL_MODE, phyAddress);
            if(res < 0)
            {   // some error
                return res;
            }
            else if(res == ETH_RES_PENDING)
            {   // retry
                return ETH_RES_PENDING;
            }

            // advance to the next phase
            DRV_ETHPHY_VendorDataSet(hClientObj, ++miiConfPhase);
            return ETH_RES_PENDING;

        case 1:
            res = DRV_ETHPHY_VendorSMIReadResultGet(hClientObj, &phyReg);
            if(res < 0)
            {   // some error
                return res;
            }
            else if(res == ETH_RES_PENDING)
            {   // retry
                return ETH_RES_PENDING;
            }

            // got PHY_REG_SPECIAL_MODE result
            // not used bits should be 0
            phyReg &= _SPECIALMODE_PHYAD_MASK | _SPECIALMODE_MODE_MASK;
            if(cFlags & ETH_PHY_CFG_RMII)
            {
                phyReg |= _SPECIALMODE_MIIMODE_MASK;
            }
            else
            {
                phyReg &= ~_SPECIALMODE_MIIMODE_MASK;
            }

            // save value for the next state
            vendorData.low = miiConfPhase + 1;
            vendorData.high = phyReg;
            DRV_ETHPHY_VendorDataSet(hClientObj, vendorData.w);
            return ETH_RES_PENDING;

        case 2:
            phyReg = vendorData.high;
            // update the Special Modes reg
            res = DRV_ETHPHY_VendorSMIWriteStart(hClientObj, PHY_REG_SPECIAL_MODE, phyReg, phyAddress);
            if(res < 0)
            {   // some error
                return res;
            }
            else if(res == ETH_RES_PENDING)
            {   // retry
                return ETH_RES_PENDING;
            }

            // done
            return ETH_RES_OK;


        default:
            // shouldn't happen
            return ETH_RES_OPERATION_ERR;
    }
    */

    // KS8999 shouldn't need any extra config, so we can skip this
    return ETH_RES_OK;
}


/****************************************************************************
 * Function:        DRV_EXTPHY_MDIXConfigure
 *
 * PreCondition:    - Communication to the PHY should have been established.
 *
 * Input:           handle - A valid open-instance handle, returned from the driver's open routine
 *					oFlags - the requested open flags: ETH_OPEN_MDIX_AUTO, ETH_OPEN_MDIX_NORM/ETH_OPEN_MDIX_SWAP
 *
 * Output:          ETH_RES_OK - operation completed successfully
 *
 *                  ETH_RES_PENDING - operation pending; the call needs to be re-issued until
 *                                    ETH_RES_OK or an error reported
 *
 *
 *                  < 0         - an error occurred and the operation was aborted
 *
 * Side Effects:    None
 *
 * Overview:        This function configures the MDIX mode for the PHY.
 *
 * Note:            None
 *****************************************************************************/
ETH_RESULT_CODE DRV_EXTPHY_MDIXConfigure(DRV_HANDLE hClientObj, ETH_OPEN_FLAGS oFlags)
{
    /*
    union
    {
        struct
        {
            uint16_t low;
            uint16_t high;
        };
        uint32_t    w;
    }vendorData;

    uint16_t    phyReg;
    uint16_t    mdixConfPhase;
    int         phyAddress;

    ETH_RESULT_CODE res = DRV_ETHPHY_VendorDataGet(hClientObj, &vendorData.w);

    if(res < 0)
    {   // some error occurred
        return res;
    }

    mdixConfPhase = vendorData.low;

    DRV_ETHPHY_PhyAddressGet(hClientObj, &phyAddress);

    switch(mdixConfPhase)
    {
        case 0:
            res = DRV_ETHPHY_VendorSMIReadStart(hClientObj, PHY_REG_SPECIAL_CTRL, phyAddress);
            if(res < 0)
            {   // some error
                return res;
            }
            else if(res == ETH_RES_PENDING)
            {   // retry
                return ETH_RES_PENDING;
            }

            // advance to the next phase
            DRV_ETHPHY_VendorDataSet(hClientObj, ++mdixConfPhase);
            return ETH_RES_PENDING;

        case 1:
            res = DRV_ETHPHY_VendorSMIReadResultGet(hClientObj, &phyReg);
            if(res < 0)
            {   // some error
                return res;
            }
            else if(res == ETH_RES_PENDING)
            {   // retry
                return ETH_RES_PENDING;
            }

            // got PHY_REG_SPECIAL_CTRL result
            // mask off not used bits
            phyReg &= _SPECIALCTRL_XPOL_MASK;

            if(oFlags & ETH_OPEN_MDIX_AUTO)
            {	// enable Auto-MDIX
                phyReg &= ~_SPECIALCTRL_AMDIXCTRL_MASK;
            }
            else
            {	// no Auto-MDIX
                phyReg |= _SPECIALCTRL_AMDIXCTRL_MASK;	// disable Auto-MDIX
                if(oFlags & ETH_OPEN_MDIX_SWAP)
                {
                    phyReg |= _SPECIALCTRL_CH_SELECT_MASK;	// swap  - MDIX
                }
                else
                {
                    phyReg &= ~_SPECIALCTRL_CH_SELECT_MASK;	// normal - MDI
                }
            }
            // save value for the next state
            vendorData.low = mdixConfPhase + 1;
            vendorData.high = phyReg;
            DRV_ETHPHY_VendorDataSet(hClientObj, vendorData.w);
            return ETH_RES_PENDING;

        case 2:
            phyReg = vendorData.high;
            // update the PHY_REG_SPECIAL_CTRL Register
            res = DRV_ETHPHY_VendorSMIWriteStart(hClientObj, PHY_REG_SPECIAL_CTRL, phyReg, phyAddress);
            if(res < 0)
            {   // some error
                return res;
            }
            else if(res == ETH_RES_PENDING)
            {   // retry
                return ETH_RES_PENDING;
            }

            // done
            return ETH_RES_OK;


        default:
            // shouldn't happen
            return ETH_RES_OPERATION_ERR;
    }
     */

    // KS8999 shouldn't need any extra config, so we can skip this
    return ETH_RES_OK;
}

/****************************************************************************
 * Function:        EthPhyMIIMClock
 *
 * PreCondition:    None
 *
 * Input:           handle - A valid open-instance handle, returned from the driver's open routine
 *
 * Output:          PHY MIIM clock, Hz
 *
 *
 * Side Effects:    None
 *
 * Overview:        This function returns the maximum clock frequency that the PHY can use for the MIIM transactions
 *
 * Note:            None
 *****************************************************************************/
unsigned int DRV_EXTPHY_SMIClockGet(DRV_HANDLE handle)
{
        // Just leave this as-is. MDC pin is only connected to test point, so it
        // shouldn't have any adverse effects.
	return 2500000;		//  2.5 MHz max clock supported
}
