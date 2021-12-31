/*
    NexDome Beaver Controller

    Copyright (C) 2021 Jasem Mutlaq (mutlaqja@ikarustech.com)
    Modified 2021 Sifan Kahale (sifan.kahale@gmail.com)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

*/
/* TODO:
    - Find a solution for setting rotator/dome parameters
      - isNumber or Switch seems to be called at start
    - Fix factory reset
    - Test alt dome rel move
    - Test network connection
    - 'Color' buttons and status correctly
*/

#include "beaver_dome.h"

#include "indicom.h"
#include "connectionplugins/connectiontcp.h"
#include "connectionplugins/connectionserial.h"

#include <cmath>
#include <cstring>
#include <cassert>
#include <memory>
#include <regex>

#include <termios.h>
#include <unistd.h>
#include "config.h"

static std::unique_ptr<Beaver> dome(new Beaver());

Beaver::Beaver()
{
    setVersion(BEAVER_VERSION_MAJOR, BEAVER_VERSION_MINOR);
    // TBD consider implementing CAN_PARK instead of having sepearte tab ... or, consolodate on Site Mgmt tab ...
    SetDomeCapability(DOME_CAN_ABORT |
                      DOME_CAN_ABS_MOVE |
                      DOME_CAN_REL_MOVE);
                      // DOME_CAN_PARK | removing this and building our own, allows us to place the fields where we want them
                      //                 creating a more unifying tab structure
                      // DOME_CAN_SYNC   this won't work - use 'set home position' instead
                      //                 dome sync will be reset any time the magnet passes over the dome cntlr!

    setDomeConnection(CONNECTION_TCP | CONNECTION_SERIAL);
}

bool Beaver::initProperties()
{
    INDI::Dome::initProperties();

    SetParkDataType(PARK_AZ);
    serialConnection->setDefaultBaudRate(Connection::Serial::B_115200);

    ///////////////////////////////////////////////////////////////////////////////
    /// Main Tab
    ///////////////////////////////////////////////////////////////////////////////
    // Rotator status
    RotatorStatusTP[0].fill("RSTATUS", "Status", "Idle");
    RotatorStatusTP.fill(getDeviceName(), "ROTATORSTATUS", "Dome", MAIN_CONTROL_TAB, IP_RO, 60, IPS_IDLE);

    // Shutter status
    ShutterStatusTP[0].fill("SSTATUS", "Status", "Idle");
    ShutterStatusTP.fill(getDeviceName(), "SHUTTERSTATUS", "Shutter", MAIN_CONTROL_TAB, IP_RO, 60, IPS_IDLE);

    // Shutter Voltage
    ShutterVoltsNP[0].fill("SHUTTERvolts", "Volts", "%.2f", 0.00, 15.00, 0.00, 0.00);
    ShutterVoltsNP.fill(getDeviceName(), "SHUTTERVOLTS", "Shutter", MAIN_CONTROL_TAB, IP_RO, 60, IPS_OK);

    // Rotator Park
    RotatorParkSP[ROTATOR_PARK].fill("ROTATOR_PARK", "Park", ISS_OFF);
    RotatorParkSP[ROTATOR_UNPARK].fill("ROTATOR_UNPARK", "UnPark", ISS_OFF);
    RotatorParkSP.fill(getDefaultName(), "ROTATOR_Park", "Rotator", MAIN_CONTROL_TAB, IP_RW, ISR_ATMOST1, 60, IPS_IDLE);

    // Rotator Home
    GotoHomeSP[0].fill("ROTATOR_HOME_GOTO", "Home", ISS_OFF);
    GotoHomeSP.fill(getDefaultName(), "ROTATOR_GOTO_Home", "Rotator", MAIN_CONTROL_TAB, IP_RW, ISR_ATMOST1, 60, IPS_IDLE);

    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Rototor settings tab
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Home position (offset from North)
    HomePositionNP[0].fill("RPOSITON", "Degrees", "%.2f", 0.0, 360.0, 0.0, 0);
    HomePositionNP.fill(getDeviceName(), "HOME_POSITION", "Home Sensor Position", ROTATOR_TAB, IP_RW, 60, IPS_IDLE);

    // Park position
    ParkPositionNP[0].fill("PPOSITON", "Degrees", "%.2f", 0.0, 360.0, 0.0, 0);
    ParkPositionNP.fill(getDeviceName(), "PARK_POSITION", "Park Position", ROTATOR_TAB, IP_RW, 60, IPS_IDLE);

    // Set Park to current
    ParkPosition2CurrentSP[0].fill("ROTATOR_PARK2CURRENT", "Set to Current", ISS_OFF);
    ParkPosition2CurrentSP.fill(getDefaultName(), "ROTATOR_PARK_CALIBRATION", "Park", ROTATOR_TAB, IP_RW, ISR_ATMOST1, 60,
                              IPS_IDLE);
    // Rotator
    RotatorCalibrationSP[ROTATOR_HOME_FIND].fill("ROTATOR_HOME_FIND", "AutoCalibrate", ISS_OFF);
    RotatorCalibrationSP[ROTATOR_HOME_MEASURE].fill("ROTATOR_HOME_MEASURE", "Measure Home", ISS_OFF);
    RotatorCalibrationSP.fill(getDefaultName(), "ROTATOR_CALIBRATION", "Rotator", ROTATOR_TAB, IP_RW, ISR_ATMOST1, 60,
                              IPS_IDLE);

    // Rotator Settings
    RotatorSettingsNP[ROTATOR_MAX_SPEED].fill("ROTATOR_MAX_SPEED", "Max Speed (m/s)", "%.f", 1, 1000, 10, 800);
    RotatorSettingsNP[ROTATOR_MIN_SPEED].fill("ROTATOR_MIN_SPEED", "Min Speed (m/s)", "%.f", 1, 1000, 10, 400);
    RotatorSettingsNP[ROTATOR_ACCELERATION].fill("ROTATOR_ACCELERATION", "Acceleration (m/s^2)", "%.f", 1, 1000, 10, 500);
    RotatorSettingsNP[ROTATOR_TIMEOUT].fill("ROTATOR_TIMEOUT", "Timeout (s)", "%.f", 1, 1000, 10, 83);
    // ALERT set to readonly for now
    RotatorSettingsNP.fill(getDeviceName(), "ROTATOR_SETTINGS", "Settings", ROTATOR_TAB, IP_RO, 60, IPS_IDLE);

    // Rotator Factory Reset
    RFactoryResetSP[0].fill("RFACTORY_RESET", "Reset", ISS_OFF);
    RFactoryResetSP.fill(getDefaultName(), "RFACTORY_Reset", "Factory", ROTATOR_TAB, IP_RW, ISR_ATMOST1, 60,
                              IPS_IDLE);

    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Shutter settings tab
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Shutter Home (calibrate, reset)
    ShutterCalibrationSP[SHUTTER_HOME_FIND].fill("SHUTTER_HOME_FIND", "AutoCalibrate", ISS_OFF);
    ShutterCalibrationSP.fill(getDeviceName(), "SHUTTER_CALIBRATION", "Shutter", SHUTTER_TAB, IP_RW, ISR_ATMOST1, 60, IPS_IDLE);

    // Shutter Settings
    ShutterSettingsNP[SHUTTER_MAX_SPEED].fill("SHUTTER_MAX_SPEED", "Max Speed (m/s)", "%.f", 1, 1000, 10, 800);
    ShutterSettingsNP[SHUTTER_MIN_SPEED].fill("SHUTTER_MIN_SPEED", "Min Speed (m/s)", "%.f", 1, 1000, 10, 400);
    ShutterSettingsNP[SHUTTER_ACCELERATION].fill("SHUTTER_ACCELERATION", "Acceleration (m/s^2)", "%.f", 1, 1000, 10, 500);
    ShutterSettingsNP[SHUTTER_SAFE_VOLTAGE].fill("SHUTTER_SAFE_VOLTAGE", "Safe Voltage", "%.1f", 10, 14, .5, 11);
    // ALERT Set to RO for now
    ShutterSettingsNP.fill(getDeviceName(), "SHUTTER_SETTINGS", "Settings", SHUTTER_TAB, IP_RO, 60, IPS_IDLE);

    // Shutter Factory Reset
    SFactoryResetSP[0].fill("SFACTORY_RESET", "Reset", ISS_OFF);
    SFactoryResetSP.fill(getDefaultName(), "SFACTORY_Reset", "Factory", ROTATOR_TAB, IP_RW, ISR_ATMOST1, 60,
                              IPS_IDLE);

    ///////////////////////////////////////////////////////////////////////////////////////////////
    // INFO Tab
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Beaver Firmware Version
    FirmwareVersionTP[0].fill("FVERSION", "Version", "");
    FirmwareVersionTP.fill(getDeviceName(), "DOME_FIRMWARE", "Beaver", CONNECTION_TAB, IP_RO, 0, IPS_IDLE);

    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Communication
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // NOTE need to figure out how to get network connection working
    tcpConnection->setDefaultHost("192.168.1.1");
    tcpConnection->setDefaultPort(10000);
    tcpConnection->setConnectionType(Connection::TCP::TYPE_UDP);
    tty_set_generic_udp_format(1);
    addDebugControl();
    return true;
}

bool Beaver::updateProperties()
{
    INDI::Dome::updateProperties();

    if (isConnected())
    {
        InitPark();

        defineProperty(&FirmwareVersionTP);
        defineProperty(&HomePositionNP);
        defineProperty(&ParkPositionNP);
        defineProperty(&ParkPosition2CurrentSP);
        defineProperty(&RotatorCalibrationSP);
        defineProperty(&GotoHomeSP);
        defineProperty(&RotatorParkSP);
        defineProperty(&RotatorSettingsNP);
        defineProperty(&RotatorStatusTP);
        //defineProperty(&RFactoryResetSP);
        if (shutterOnLine()) {
            defineProperty(&ShutterCalibrationSP);
            defineProperty(&ShutterSettingsNP);
            defineProperty(&ShutterStatusTP);
            defineProperty(&ShutterVoltsNP);
            //defineProperty(&SFactoryResetSP);
        }
    }
    else
    {
        deleteProperty(FirmwareVersionTP.getName());
        deleteProperty(RotatorCalibrationSP.getName());
        deleteProperty(GotoHomeSP.getName());
        deleteProperty(HomePositionNP.getName());
        deleteProperty(ParkPositionNP.getName());
        deleteProperty(ParkPosition2CurrentSP.getName());
        deleteProperty(RotatorSettingsNP.getName());
        deleteProperty(RotatorParkSP.getName());
        deleteProperty(RotatorStatusTP.getName());
        //deleteProperty(RFactoryResetSP.getName());
        deleteProperty(ShutterCalibrationSP.getName());
        deleteProperty(ShutterSettingsNP.getName());
        deleteProperty(ShutterStatusTP.getName());
        deleteProperty(ShutterVoltsNP.getName());
        //deleteProperty(SFactoryResetSP.getName());

    }

    return true;
}


//////////////////////////////////////////////////////////////////////////////
///  Handshake
//////////////////////////////////////////////////////////////////////////////
bool Beaver::Handshake()
{
    if (echo()) {
        // Check if shutter is online
        if (shutterOnLine()) {
            LOG_DEBUG("Shutter in online, enabling Dome has shutter property");
            SetDomeCapability(GetDomeCapability() | DOME_HAS_SHUTTER);
            return true;
        }
        return true;
    }

    return false;
}

//////////////////////////////////////////////////////////////////////////////
/// Set default name
//////////////////////////////////////////////////////////////////////////////
const char *Beaver::getDefaultName()
{
    return  "Beaver Dome";
}

//////////////////////////////////////////////////////////////////////////////
/// Extended Handshake
//////////////////////////////////////////////////////////////////////////////
bool Beaver::echo()
{
    //NOTE perhaps set a flag for a false, then check at end to return false, thereby allowing other checks to occur
    double res = 0;
    // retrieve the version from the dome
    char result[DRIVER_LEN] = {0};
    if (!sendRawCommand("!seletek tversion#", result)) {
        LOG_ERROR("Error getting version info");
        return false;
    }
    std::string resString = result;
    LOGF_DEBUG("Version string returned %s", resString.c_str());

    std::regex e(R"(.*:\d*:(.*))");
    std::sregex_iterator iter(resString.begin(), resString.end(), e);
    //std::sregex_iterator end;

    FirmwareVersionTP[0].setText((*iter)[1]);

    // retrieve the current az from the dome
    if (!sendCommand("!dome getaz#", res))
        return false;
    else {
        DomeAbsPosN[0].value = res;
        LOGF_INFO("Dome reports currently at az: %.1f", res);
    }
    // retrieve the current home offset from the dome
    if (!sendCommand("!domerot gethome#", res)) 
        return false;
    else {
        HomePositionNP[0].setValue(res);
        LOGF_INFO("Dome reports home offset: %f", res);
    }
    // retrieve the current park position from the dome
    if (!sendCommand("!domerot getpark#", res)) 
        return false;
    else {
        ParkPositionNP[0].value = res;
        LOGF_INFO("Dome reports park az as: %.1f", res);
    }
    
    // get current rotator settings
    if (!rotatorGetSettings())
        return false;
    // get current shutter settings
    if (shutterOnLine()) {
        if (!shutterGetSettings())
            return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////
/// Switch field updated
//////////////////////////////////////////////////////////////////////////////
bool Beaver::ISNewSwitch(const char *dev, const char *name, ISState *states, char *names[], int n)
{
    if (dev != nullptr && strcmp(dev, getDeviceName()) == 0)
    {
        /////////////////////////////////////////////
        // Rotator Calibration (find and measure home)
        /////////////////////////////////////////////
        if (RotatorCalibrationSP.isNameMatch(name))
        {
            RotatorCalibrationSP.update(states, names, n);
            bool rc = false;
            switch (RotatorCalibrationSP.findOnSwitchIndex())
            {
                case ROTATOR_HOME_FIND:
                    rc = rotatorFindHome();
                    RotatorCalibrationSP.setState(rc ? IPS_BUSY : IPS_ALERT);
                    break;

                case ROTATOR_HOME_MEASURE:
                    rc = rotatorMeasureHome();
                    RotatorCalibrationSP.setState(rc ? IPS_BUSY : IPS_ALERT);
                    break;
            }
            RotatorCalibrationSP.apply();
            return true;
        }
        
        /////////////////////////////////////////////
        // Rotator Go Home
        /////////////////////////////////////////////
        if (GotoHomeSP.isNameMatch(name))
        {
            GotoHomeSP.update(states, names, n);
            bool rc = false;
            rc = rotatorGotoHome();
            GotoHomeSP.setState(rc ? IPS_BUSY : IPS_ALERT);
            GotoHomeSP.apply();
            return true;
        }

        /////////////////////////////////////////////
        // Set Park to current position
        /////////////////////////////////////////////
        if (ParkPosition2CurrentSP.isNameMatch(name))
        {
            ParkPosition2CurrentSP.update(states, names, n);
            bool rc = false;
            rc = rotatorSetPark(rotatorGetAz());
            ParkPosition2CurrentSP.setState(rc ? IPS_OK : IPS_ALERT);
            ParkPosition2CurrentSP.apply();
            return true;
        }

        /////////////////////////////////////////////
        // Rotator Park
        /////////////////////////////////////////////
        if (RotatorParkSP.isNameMatch(name))
        {
            RotatorParkSP.update(states, names, n);
            bool rc = false;
            switch (RotatorParkSP.findOnSwitchIndex())
            {
                case ROTATOR_PARK:
                    rc = rotatorGotoPark();
                    RotatorParkSP.setState(rc ? IPS_BUSY : IPS_ALERT);
                    break;
                case ROTATOR_UNPARK:
                    rc = rotatorUnPark();
                    RotatorParkSP.setState(rc ? IPS_OK : IPS_ALERT);
                    break;
            }
            RotatorParkSP.apply();
            return true;
        }

        /////////////////////////////////////////////
        // Shutter Calibration
        /////////////////////////////////////////////
        if (ShutterCalibrationSP.isNameMatch(name))
        {  //TEST
            ShutterCalibrationSP.update(states, names, n);
            bool rc = shutterFindHome();
            if (rc)
                setShutterState(SHUTTER_MOVING);
            ShutterCalibrationSP.setState(rc ? IPS_BUSY : IPS_ALERT);
            ShutterCalibrationSP.apply();
            return true;
        }
        /////////////////////////////////////////////
        // Rotator Factory Reset
        /////////////////////////////////////////////
        if (RFactoryResetSP.isNameMatch(name))
        {  // ALERT TODO not working!
            double res = 0;
            RFactoryResetSP.update(states, names, n);
            if (!sendCommand("!seletek resetfs 1#", res)) {
                LOG_ERROR("Problem doing a rotator factory reset");
                RFactoryResetSP.setState(IPS_ALERT);
                return false;
            }
            sleep(1000);
            if (!sendCommand("!seletek reboot#", res)) {
                LOG_ERROR("Problem doing a rotator factory reset");
                RFactoryResetSP.setState(IPS_ALERT);
                return false;
            }
            LOG_WARN("Just performed a rotator factory reset");
            RFactoryResetSP.setState(IPS_OK);
            RFactoryResetSP.apply();
            return true;
        }
        /////////////////////////////////////////////
        // Shutter Factory Reset
        /////////////////////////////////////////////
        if (SFactoryResetSP.isNameMatch(name))
        {  // TODO test
            double res = 0;
            SFactoryResetSP.update(states, names, n);
            if (!sendCommand("!dome sendtoshutter \"seletek resetfs 1\"#", res)) {
                LOG_ERROR("Problem doing a shutter factory reset");
                SFactoryResetSP.setState(IPS_ALERT);
                return false;
            }
            sleep(1000);
            if (!sendCommand("!dome sendtoshutter \"seletek reboot\"#", res)) {
                LOG_ERROR("Problem doing a rotator factory reset");
                RFactoryResetSP.setState(IPS_ALERT);
                return false;
            }
            LOG_WARN("Just performed a shutter factory reset");
            SFactoryResetSP.setState(IPS_OK);
            SFactoryResetSP.apply();
            return true;
        }
    }

    return INDI::Dome::ISNewSwitch(dev, name, states, names, n);
}

//////////////////////////////////////////////////////////////////////////////
/// Number field updated
//////////////////////////////////////////////////////////////////////////////
bool Beaver::ISNewNumber(const char *dev, const char *name, double values[], char *names[], int n)
{
    if (dev != nullptr && strcmp(dev, getDeviceName()) == 0)
    {
        /*********************************** not working, leaving out for now
        /////////////////////////////////////////////
        // Rotator Settings
        /////////////////////////////////////////////
        if ((RotatorSettingsNP.isNameMatch(name)) && hasInited)    // TODO does not seem to be updating the cntlr
        {
            LOG_DEBUG("Rotator settings have been modified");
            RotatorSettingsNP.update(values, names, n);
            RotatorSettingsNP.setState(rotatorSetSettings(RotatorSettingsNP[ROTATOR_MAX_SPEED].getValue(),
                                       RotatorSettingsNP[ROTATOR_MIN_SPEED].getValue(),
                                       RotatorSettingsNP[ROTATOR_ACCELERATION].getValue(),
                                       RotatorSettingsNP[ROTATOR_TIMEOUT].getValue()) ? IPS_OK : IPS_ALERT);
            RotatorSettingsNP.apply();
            return true;
        }
        // this is being activated on start !
        /////////////////////////////////////////////
        // Shutter Settings
        /////////////////////////////////////////////
        if ((ShutterSettingsNP.isNameMatch(name))  && hasInited)    // TODO does not seem to be updating the cntlr
        {
            ShutterSettingsNP.update(values, names, n);
            LOG_DEBUG("Shutter settings have been modified");
            ShutterSettingsNP.setState(shutterSetSettings(ShutterSettingsNP[SHUTTER_MAX_SPEED].getValue(),
                                       ShutterSettingsNP[SHUTTER_MIN_SPEED].getValue(),
                                       ShutterSettingsNP[SHUTTER_ACCELERATION].getValue(),
                                       ShutterSettingsNP[SHUTTER_SAFE_VOLTAGE].getValue()) ? IPS_OK : IPS_ALERT);
            ShutterCalibrationSP.apply();
            return true;
        }
        ******************************************/

        ///////////////////////////////////////////////////////////////////////////////
        /// Home Position
        ///////////////////////////////////////////////////////////////////////////////
        if ((HomePositionNP.isNameMatch(name)) && hasInited)
        {
            LOG_DEBUG("Home pos settings have been modified");
            HomePositionNP.update(values, names, n);
            if (rotatorSetHome(HomePositionNP[0].getValue())) {
                LOGF_INFO("Home position is updated to %.1f degrees.", HomePositionNP[0].getValue());
                HomePositionNP.apply();
                return true;
            }
            else
                return false;
        }
        
        ///////////////////////////////////////////////////////////////////////////////
        /// Park Position
        ///////////////////////////////////////////////////////////////////////////////
        if ((ParkPositionNP.isNameMatch(name)) && hasInited)
        {
            LOG_DEBUG("Park pos settings have been modified");
            ParkPositionNP.update(values, names, n);
            if (rotatorSetPark(ParkPositionNP[0].getValue())) {
                LOGF_INFO("Home position is updated to %.1f degrees.", ParkPositionNP[0].getValue());
                ParkPositionNP.apply();
                return true;
            }
            else
                return false;
        }

    }

    return INDI::Dome::ISNewNumber(dev, name, values, names, n);
    
}

///////////////////////////////////////////////////////////////////////////
/// Timer hit - update appropriate fields
///////////////////////////////////////////////////////////////////////////
void Beaver::TimerHit()
{
    if (!isConnected()) {
        return;
    }
    
    // Query rotator status
    double res = 0;
    if (!sendCommand("!dome status#", res))
        LOG_ERROR("Status command error");
    
    uint16_t domeStatus = 0;
    if (!getDomeStatus(domeStatus)) {
        LOG_ERROR("Could not get dome status");
    }
    // Test for general dome errors
    if (domeStatus & DOME_STATUS_UNSAFE_CW) {
        LOG_ERROR("CW Unsafe Error");
        setDomeState(DOME_ERROR);
        RotatorStatusTP.apply();
    }
    if (domeStatus & DOME_STATUS_UNSAFE_RG) {
        LOG_ERROR("RGx Unsafe Error");
        setDomeState(DOME_ERROR);
        RotatorStatusTP.apply();
    }
    
    // Get Position
    rotatorGetAz();
    LOGF_DEBUG("Rotator position: %f", DomeAbsPosN[0].value);

    // TODO when Find/Measure/Goto home is finished, set field to green (from yellow)
    // Check rotator
    if (getDomeState() == DOME_MOVING || getDomeState() == DOME_UNPARKING) {
        LOGF_DEBUG("dome status: %00x", domeStatus);
        if ((domeStatus & DOME_STATUS_ROTATOR_MOVING) == 0) {
            setDomeState(DOME_IDLE);
            RotatorStatusTP[0].setText("Idle");
            RotatorStatusTP.apply();
            LOGF_DEBUG("Dome state set to IDLE, domestatus: %00x", domeStatus);
        }
        if (domeStatus & DOME_STATUS_ROTATOR_HOME) {
            setDomeState(DOME_IDLE);
            RotatorStatusTP[0].setText("At Home/Idle");
            RotatorStatusTP.apply();
            LOG_DEBUG("Dome state set to HOME");
        }
        if (domeStatus & DOME_STATUS_ROTATOR_ERROR) {
            setDomeState(DOME_ERROR);
            RotatorStatusTP[0].setText("Error");
            RotatorStatusTP.apply();
            LOG_ERROR("Rotation Mechanical Error");
        }
    }
    // Dome parked is a special case
    // TODO once parked, it still says 'parking'
    // TEST also need to set status to OK
    if ((getDomeState() == DOME_PARKING) & (domeStatus & DOME_STATUS_ROTATOR_PARKED)) {
        setDomeState(DOME_PARKED);
        RotatorStatusTP[0].setText("Parked");
        RotatorStatusTP.setState(IPS_OK);
        RotatorStatusTP.apply();
        RotatorParkSP.setState(IPS_OK);
        RotatorParkSP.apply();

        LOG_DEBUG("Dome state set to PARKED");
    }
    
    // TODO if shutter goes offline during a session, need to reset capabilities ... take out menu items, etc.
    if (getShutterState() == SHUTTER_MOVING) {
        if (domeStatus & DOME_STATUS_SHUTTER_MOVING) {
            setShutterState(SHUTTER_MOVING);
            ShutterStatusTP[0].setText("Open");
            LOG_DEBUG("Shutter state set to OPENED");
        }
        if (domeStatus & DOME_STATUS_SHUTTER_CLOSED) {
            setShutterState(SHUTTER_CLOSED);
            ShutterStatusTP[0].setText("Closed");
            LOG_DEBUG("Shutter state set to CLOSED");
        }
        if (domeStatus & DOME_STATUS_SHUTTER_OPENED) {
            setShutterState(SHUTTER_OPENED);
            ShutterStatusTP[0].setText("Open");
            LOG_DEBUG("Shutter state set to OPEN");
        }
        if (domeStatus & DOME_STATUS_SHUTTER_OPENING) {
            setShutterState(SHUTTER_MOVING);
            ShutterStatusTP[0].setText("Opening");
            LOG_DEBUG("Shutter state set to Opening");
        }
        if (domeStatus & DOME_STATUS_SHUTTER_CLOSING) {
            setShutterState(SHUTTER_MOVING);
            ShutterStatusTP[0].setText("Closing");
            LOG_DEBUG("Shutter state set to Closing");
        }
        if (domeStatus & DOME_STATUS_SHUTTER_ERROR) {
            LOG_ERROR("Shutter Mechanical Error");
            ShutterStatusTP[0].setText("Mechanical Error");
            setShutterState(SHUTTER_ERROR);
        }
        if (domeStatus & DOME_STATUS_SHUTTER_COMM) {
            LOG_ERROR("Shutter Communications Error");
            ShutterStatusTP[0].setText("Communications Error");
            setShutterState(SHUTTER_ERROR);
        }
        ShutterStatusTP.apply();
    }
    
    // Update shutter voltage
    if (shutterOnLine()) {
        if (!sendCommand("!dome getshutterbatvoltage#", res))
            LOG_ERROR("Shutter voltage command error");
        else {
            LOGF_DEBUG("Shutter voltage currently is: %.2f", res);
            ShutterVoltsNP[0].setValue(res);
            //TODO how can I color the button, not the circle?
            //(res < ShutterSettingsNP[SHUTTER_SAFE_VOLTAGE].getValue()) ? ShutterVoltsNP.setState(IPS_ALERT) : ShutterVoltsNP.setState(IPS_OK);
            ShutterVoltsNP.apply();
        }
    }

    //TODO how can I color the button, not the circle?
    //       this is an attempt to prevent the set shutter and rotator at initialization
    hasInited = true;


    SetTimer(getCurrentPollingPeriod());
}

//////////////////////////////////////////////////////////////////////////////
/// Rotator absolute move
//////////////////////////////////////////////////////////////////////////////
IPState Beaver::MoveAbs(double az)
{
    // ALERT updates abs location 'after' next move (always one behind)
    if (rotatorGotoAz(az))
    {
        m_TargetRotatorAz = az;
        setDomeState(DOME_MOVING);
        RotatorStatusTP[0].setText("Moving");
        RotatorStatusTP.apply();
        return IPS_BUSY;
    }
    return IPS_ALERT;
}

//////////////////////////////////////////////////////////////////////////////
/// Rotator relative move (calc's offset and calles abs move)
//////////////////////////////////////////////////////////////////////////////
IPState Beaver::MoveRel(double azDiff)
{

    azDiff = domeDir * azDiff;
    m_TargetRotatorAz = DomeAbsPosN[0].value + azDiff;

    if (m_TargetRotatorAz < DomeAbsPosN[0].min)
        m_TargetRotatorAz += DomeAbsPosN[0].max;
    if (m_TargetRotatorAz > DomeAbsPosN[0].max)
        m_TargetRotatorAz -= DomeAbsPosN[0].max;
    LOGF_DEBUG("Requested rel move of %.1f", azDiff);
    lastAzDiff = fabs(azDiff);
    return MoveAbs(m_TargetRotatorAz);
}

//////////////////////////////////////////////////////////////////////////////
/// Rotator move (calc's offset and calles abs move)
//////////////////////////////////////////////////////////////////////////////
IPState Beaver::Move(DomeDirection dir, DomeMotionCommand operation)
 {
    // Map to button outputs
    LOG_DEBUG("Re-implemented move was called");
     if (operation == MOTION_START)
     {
         if (dir == DOME_CW) {
             domeDir = 1;
         }
         else {
             domeDir = -1;
         }
         MoveRel(lastAzDiff);

     }
     return IPS_OK;
 }

//////////////////////////////////////////////////////////////////////////////
/// open or close the shutter (will not show if shutter is not present)
//////////////////////////////////////////////////////////////////////////////
IPState Beaver::ControlShutter(ShutterOperation operation)
{
    double res = 0;
    if (operation == SHUTTER_OPEN)
    {
        if (sendCommand("!dome openshutter#", res))
            return IPS_BUSY;
    }
    else if (operation == SHUTTER_CLOSE)
    {
        if (sendCommand("!dome closeshutter#", res))
            return IPS_BUSY;
    }
    return IPS_ALERT;
}

//////////////////////////////////////////////////////////////////////////////
/// abort everything
//////////////////////////////////////////////////////////////////////////////
bool Beaver::Abort()
{
    return abortAll();
}

//////////////////////////////////////////////////////////////////////////////
/// INDI save config
//////////////////////////////////////////////////////////////////////////////
bool Beaver::saveConfigItems(FILE *fp)
{
    INDI::Dome::saveConfigItems(fp);
    //IUSaveConfigNumber(fp, &ShutterSettingsNP);  //these are all save in the controller and read from there at startup
    //IUSaveConfigNumber(fp, &RotatorSettingsNP);
    //IUSaveConfigNumber(fp, &HomePositionNP);
    //IUSaveConfigNumber(fp, &ParkPositionNP);
    return true;
}

/////////////////////////////////////////////////////////////////////////////
/// tells rotator to goto az pos
/////////////////////////////////////////////////////////////////////////////
bool Beaver::rotatorGotoAz(double az)
{
    char cmd[DRIVER_LEN] = {0};
    double res = 0;
    snprintf(cmd, DRIVER_LEN, "!dome gotoaz %.2f#", az);
    setDomeState(DOME_MOVING);
    RotatorStatusTP[0].setText("Moving");
    RotatorStatusTP.apply();
    return sendCommand(cmd, res);
}

/////////////////////////////////////////////////////////////////////////////
/// rotator az position
/////////////////////////////////////////////////////////////////////////////
bool Beaver::rotatorGetAz()
{
    double res = 0;
    if (sendCommand("!dome getaz#", res))
    {
        DomeAbsPosN[0].value = res;
        // TODO Need to update Abs position on main tab
        //DomeAbsPosNP.apply();
        return true;
    }
    return false;
}

/****************************** not used
/////////////////////////////////////////////////////////////////////////////
///  Sync (should not use this!) redefines current az to entered value
/////////////////////////////////////////////////////////////////////////////
bool Beaver::rotatorSyncAZ(double az)
{
    char cmd[DRIVER_LEN] = {0};
    double res = 0;
    snprintf(cmd, DRIVER_LEN, "!dome setaz %.2f#", az);
    return sendCommand(cmd, res);
}
******************************/

/////////////////////////////////////////////////////////////////////////////
/// Set home offset from north
/////////////////////////////////////////////////////////////////////////////
// NOTE indi_dome has a HOME_POSITION, described as: dome home position in absolute degrees azimuth, should use this instead?
bool Beaver::rotatorSetHome(double az)
{
    char cmd[DRIVER_LEN] = {0};
    double res = 0;
    snprintf(cmd, DRIVER_LEN, "!domerot sethome %.2f#", az);
    return sendCommand(cmd, res);
}

// NOTE what about a set park?
/////////////////////////////////////////////////////////////////////////////
/// Set home offset from north
/////////////////////////////////////////////////////////////////////////////
bool Beaver::rotatorSetPark(double az)
{
    char cmd[DRIVER_LEN] = {0};
    double res = 0;
    snprintf(cmd, DRIVER_LEN, "!domerot setpark %.2f#", az);
    return sendCommand(cmd, res);
}

/////////////////////////////////////////////////////////////////////////////
/// Rotator park
/////////////////////////////////////////////////////////////////////////////
bool Beaver::rotatorGotoPark()
{
    double res = 0;
    setDomeState(DOME_PARKING);
    RotatorStatusTP[0].setText("Parking");
    RotatorStatusTP.apply();
    return sendCommand("!dome gopark#", res);
}

/////////////////////////////////////////////////////////////////////////////
/// Rotator unpark
/////////////////////////////////////////////////////////////////////////////
bool Beaver::rotatorUnPark()
{
    setDomeState(DOME_IDLE);
    RotatorStatusTP[0].setText("Idle @ park");
    RotatorStatusTP.apply();
    return true;
}

/////////////////////////////////////////////////////////////////////////////
/// Rotator set park position
/////////////////////////////////////////////////////////////////////////////
bool Beaver::rotatorSetPark()
{
    double res = 0;
    setDomeState(DOME_PARKED);
    RotatorStatusTP[0].setText("Parked");
    RotatorStatusTP.apply();
    return sendCommand("!dome setpark#", res);
}

/////////////////////////////////////////////////////////////////////////////
/// tells rotator to goto home position
/////////////////////////////////////////////////////////////////////////////
bool Beaver::rotatorGotoHome()
{
    double res = 0;
    setDomeState(DOME_MOVING);
    RotatorStatusTP[0].setText("Homing");
    RotatorStatusTP.apply();
    return sendCommand("!dome gohome#", res);
}

/////////////////////////////////////////////////////////////////////////////
/// tells the rotator to find and accurate measure the home pos and set all params
/////////////////////////////////////////////////////////////////////////////
bool Beaver::rotatorMeasureHome()
{
    double res = 0;
    setDomeState(DOME_MOVING);
    RotatorStatusTP[0].setText("Measuring Home");
    RotatorStatusTP.apply();
    return sendCommand("!dome autocalrot 1#", res);
}

/////////////////////////////////////////////////////////////////////////////
/// tell the rotator to find the home position magnet
/////////////////////////////////////////////////////////////////////////////
bool Beaver::rotatorFindHome()
{
    double res = 0;
    setDomeState(DOME_MOVING);
    RotatorStatusTP[0].setText("Finding Home");
    RotatorStatusTP.apply();
    return sendCommand("!dome autocalrot 0#", res);
}

/************* not used
/////////////////////////////////////////////////////////////////////////////
/// Rotator at home?
/////////////////////////////////////////////////////////////////////////////
bool Beaver::rotatorIsHome()
{
    double status = 0;
    if (sendCommand("!dome athome#", status)) {
        LOG_ERROR("Error checking home");
        return false;
    }
    LOGF_INFO("DIAG Rotator Home? %s", (status == 1) ? "true" : "false");
    if (status == 1) {
        RotatorStatusTP[0].setText("Home");
        RotatorStatusTP.apply();
        return true;
    }
    return false;
}


/////////////////////////////////////////////////////////////////////////////
/// Rotator parked?
/////////////////////////////////////////////////////////////////////////////
bool Beaver::rotatorIsParked()
{
    double status = 0;
    if (!sendCommand("!dome atpark#", status)) {
        LOG_ERROR("Error checking park");
        return false;
    }
    LOGF_INFO("DIAG Rotator Parked? %s", (status == 1) ? "true" : "false");

    if (status == 1) {
        RotatorStatusTP[0].setText("Parked");
        RotatorStatusTP.apply();
        return true;
    }
    return false;
}
**********/


/////////////////////////////////////////////////////////////////////////////
///
/////////////////////////////////////////////////////////////////////////////
bool Beaver::getDomeStatus(uint16_t &domeStatus)
{
    double res = 0;
    if (!sendCommand("!dome status#", res))  {
        LOG_ERROR("Status cmd errored out");
        return false;
    }
    domeStatus = static_cast<uint16_t>(res);
    LOGF_DEBUG("Dome status: %0x", domeStatus);
    return true;
}

/////////////////////////////////////////////////////////////////////////////
///
/////////////////////////////////////////////////////////////////////////////
bool Beaver::shutterOnLine()
{
    // Shutter is considered online if it's status is ok and no comm error
    double res = 0;
    uint16_t domeStatus;
    bool shutterIsUp = false;
    // retrieving shutter status
    if (!sendCommand("!dome shutterisup#", res))  {
        LOG_ERROR("Shutter status cmd errored out");
        //failsave, return false/not online
        return false;
    }
    // retrieving comm status
    shutterIsUp = static_cast<bool>(res);
    if (!getDomeStatus(domeStatus)) {
        LOG_ERROR("Shutter status cmd errored out");
        //failsave, return false/not online
        return false;
    }
    LOGF_DEBUG("ShutterIsUp %s  Comms error %s", shutterIsUp ? "true" : "false", (domeStatus & DOME_STATUS_SHUTTER_COMM) ? "true" : "false");
    bool status = (shutterIsUp |  !(domeStatus & DOME_STATUS_SHUTTER_COMM));
    LOGF_DEBUG("ShuttOnLine %s", status ? "true" : "false");
    return status;
}

/////////////////////////////////////////////////////////////////////////////
///
/////////////////////////////////////////////////////////////////////////////
bool Beaver::abortAll()
{
    double res = 0;
    if (sendCommand("!dome abort 1 1 1#", res)) {
        RotatorStatusTP[0].setText("Idle");
        RotatorStatusTP.apply();
        if (!rotatorGetAz())
            return false;
        return true;
    }
        
    return false;
}

/////////////////////////////////////////////////////////////////////////////
///
/////////////////////////////////////////////////////////////////////////////
bool Beaver::shutterAbort()
{
    double res = 0;
    return sendCommand("!dome abort 0 0 1#", res);
}

/////////////////////////////////////////////////////////////////////////////
/// Shutter set settings
/////////////////////////////////////////////////////////////////////////////
bool Beaver::shutterSetSettings(double maxSpeed, double minSpeed, double acceleration, double voltage)
{
    INDI_UNUSED(maxSpeed);
    INDI_UNUSED(minSpeed);
    INDI_UNUSED(acceleration);
    INDI_UNUSED(voltage);
    // ALERT Commented out for now, it set everything to zero on init!
    // TODO this is not updating
    /***********
    if (hasInited) {
        if (shutterOnLine()) {
            if (!sendCommand("!dome setshuttermaxspeed#", maxSpeed)) {
                LOG_ERROR("Problem setting shutter max speed");
                return false;
            }
            if (!sendCommand("!dome setshutterminspeed#", minSpeed)) {
                LOG_ERROR("Problem setting shutter min speed");
                return false;
            }
            if (!sendCommand("!dome setshutteracceleration#", acceleration)) {
                LOG_ERROR("Problem setting shutter acceleration");
                return false;
            }
            if (!sendCommand("!dome setshuttersafevoltage#", voltage)) {  //TODO might be issue setting .x eg 11.5
                LOG_ERROR("Problem setting shutter safe voltage");
                return false;
            }
            double res = 0;
            if(!sendCommand("!seletek savefs#", res)) {
                LOG_ERROR("Problem setting shutter savefs");
                return false;
            }

            LOG_DEBUG("We set the shutters ok");
        }
    }
    *************/
    return true;
}

/////////////////////////////////////////////////////////////////////////////
/// Shutter get settings
/////////////////////////////////////////////////////////////////////////////
bool Beaver::shutterGetSettings()
{
    double res;
    if (shutterOnLine()) {
        if (!sendCommand("!dome getshuttermaxspeed#", res)) {
            LOG_ERROR("Problem getting shutter max speed");
            return false;
        }
        else {
            ShutterSettingsNP[SHUTTER_MAX_SPEED].setValue(res);
            LOGF_DEBUG("Shutter reports max speed of: %.1f", res);
        }
        if (!sendCommand("!dome getshutterminspeed#", res)) {
            LOG_ERROR("Problem getting shutter min speed");
            return false;
        }
        else {
            ShutterSettingsNP[SHUTTER_MIN_SPEED].setValue(res);
            LOGF_DEBUG("Shutter reports min speed of: %.1f", res);
        }
        if (!sendCommand("!dome getshutteracceleration#", res)) {
            LOG_ERROR("Problem getting shutter acceleration");
            return false;
        }
        else {
            ShutterSettingsNP[SHUTTER_ACCELERATION].setValue(res);
            LOGF_DEBUG("Shutter reports acceleration of: %.1f", res);
        }
        if (!sendCommand("!dome getshuttersafevoltage#", res)) {
            LOG_ERROR("Problem getting shutter safe voltage");
            return false;
        }
        else {
            ShutterSettingsNP[SHUTTER_SAFE_VOLTAGE].setValue(res);
            LOGF_DEBUG("Shutter reports safe voltage of: %.1f", res);
        }
        ShutterSettingsNP.apply();
    }

    return true;
}

/////////////////////////////////////////////////////////////////////////////
/// Rotator set settings
/////////////////////////////////////////////////////////////////////////////
bool Beaver::rotatorSetSettings(double maxSpeed, double minSpeed, double acceleration, double timeout)
{
    INDI_UNUSED(maxSpeed);
    INDI_UNUSED(minSpeed);
    INDI_UNUSED(acceleration);
    INDI_UNUSED(timeout);
    // ALERT Commented out for now, it set everything to zero on init!
    // TODO not working
    /**************
    if (hasInited) {
        if (!sendCommand("!domerot setmaxspeed#", maxSpeed)) {
            LOG_ERROR("Problem setting rotator max speed");
            return false;
        }
        if (!sendCommand("!domerot setminspeed#", minSpeed)) {
            LOG_ERROR("Problem setting rotator min speed");
            return false;
        }
        if (!sendCommand("!domerot setacceleration#", acceleration)) {
            LOG_ERROR("Problem setting rotator acceleration");
            return false;
        }
        if (!sendCommand("!domerot setmaxfullrotsecs#", timeout)) {
            LOG_ERROR("Problem setting rotator full rot secs");
            return false;
        }
        double res = 0;
        if(!sendCommand("!seletek savefs#", res)) {
            LOG_ERROR("dome could not savefs");
            return false;
        }
    }
    ***************/
    return true;
}

/////////////////////////////////////////////////////////////////////////////
/// Rotator get settings
/////////////////////////////////////////////////////////////////////////////
bool Beaver::rotatorGetSettings()
{
    double res;
    if (!sendCommand("!domerot getmaxspeed#", res)) {
        LOG_ERROR("Problem getting rotator max speed");
        return false;
    }
    else {
        RotatorSettingsNP[ROTATOR_MAX_SPEED].setValue(res);
        LOGF_DEBUG("Rotator reports max speed of: %.1f", res);
    }
    if (!sendCommand("!domerot getminspeed#", res)) {
        LOG_ERROR("Problem getting rotator min speed");
        return false;
    }
    else {
        RotatorSettingsNP[ROTATOR_MIN_SPEED].setValue(res);
        LOGF_DEBUG("Rotator reports min speed of: %.1f", res);
    }
    if (!sendCommand("!domerot getacceleration#", res)) {
        LOG_ERROR("Problem getting rotator acceleration");
        return false;
    }
    else {
        RotatorSettingsNP[ROTATOR_ACCELERATION].setValue(res);
        LOGF_DEBUG("Rotator reports acceleration of: %.1f", res);
    }
    if (!sendCommand("!domerot getmaxfullrotsecs#", res)) {
        LOG_ERROR("Problem getting rotator full rot secs");
        return false;
    }
    else {
        RotatorSettingsNP[ROTATOR_TIMEOUT].setValue(res);
        LOGF_DEBUG("Rotator reports timeout(s) of: %.1f", res);
    }
    RotatorSettingsNP.apply();

    return true;
}

/////////////////////////////////////////////////////////////////////////////
///
/////////////////////////////////////////////////////////////////////////////
bool Beaver::shutterFindHome()
{
    if (shutterOnLine()) {
        double res = 0;
        return sendCommand("!dome autocalshutter#", res);
    }
    return false;
}

/////////////////////////////////////////////////////////////////////////////
/// Send Raw Command
/////////////////////////////////////////////////////////////////////////////
bool Beaver::sendRawCommand(const char * cmd, char * response)
{
    int rc = TTY_OK;
    for (int i = 0; i < 3; i++)
    {
        int nbytes_written = 0, nbytes_read = 0;
        //char response[DRIVER_LEN] = {0};

        rc = tty_write_string(PortFD, cmd, &nbytes_written);

        if (rc != TTY_OK)
        {
            char errstr[MAXRBUF] = {0};
            tty_error_msg(rc, errstr, MAXRBUF);
            LOGF_ERROR("Serial write error: %s.", errstr);
            return false;
        }

        rc = tty_nread_section(PortFD, response, DRIVER_LEN, DRIVER_STOP_CHAR, DRIVER_TIMEOUT, &nbytes_read);

        if (rc != TTY_OK)
        {
            usleep(100000);
            continue;
        }
        if (rc != TTY_OK) {
            char errstr[MAXRBUF] = {0};
            tty_error_msg(rc, errstr, MAXRBUF);
            LOGF_ERROR("Serial read error: %s.", errstr);
        }
        // Remove extra #
        response[nbytes_read - 1] = 0;
        LOGF_DEBUG("Command Response: %s", response);
    }

    return true;
}

/*********** previous
/////////////////////////////////////////////////////////////////////////////
/// Send Command
/////////////////////////////////////////////////////////////////////////////
bool Beaver::sendCommand(const char * cmd, double &res)
{
    int rc = TTY_OK;
    for (int i = 0; i < 3; i++)
    {
        int nbytes_written = 0, nbytes_read = 0;
        char response[DRIVER_LEN] = {0};

        rc = tty_write_string(PortFD, cmd, &nbytes_written);

        if (rc != TTY_OK)
        {
            char errstr[MAXRBUF] = {0};
            tty_error_msg(rc, errstr, MAXRBUF);
            LOGF_ERROR("Serial write error: %s.", errstr);
            return false;
        }

        rc = tty_nread_section(PortFD, response, DRIVER_LEN, DRIVER_STOP_CHAR, DRIVER_TIMEOUT, &nbytes_read);

        if (rc != TTY_OK)
        {
            usleep(100000);
            continue;
        }

        // Remove extra #
        response[nbytes_read - 1] = 0;
        LOGF_DEBUG("Command Response: %s", response);
        ***************/

/////////////////////////////////////////////////////////////////////////////
/// Send Command
/////////////////////////////////////////////////////////////////////////////
bool Beaver::sendCommand(const char * cmd, double &res)
{
    // TODO due to version requiring text not double, need to create separate function of
    //      above and call this from below and the version in echo()
    char response[DRIVER_LEN] = {0};
    sendRawCommand(cmd, response);

    std::regex rgx(R"(.*:((\d+(\.\d*)*)))");  // changed to accept int or float
    std::smatch match;
    std::string input(response);

    if (std::regex_search(input, match, rgx)) {
        try {
            res = std::stof(match.str(1));
            return true;
        }
        catch (...) {
            LOGF_ERROR("Failed to process response: %s.", response);
            return false;
        }
    }

    LOGF_INFO("Command sent: %s  response: %d", cmd, res);

    return false;
}
