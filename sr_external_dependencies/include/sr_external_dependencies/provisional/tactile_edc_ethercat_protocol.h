//
// © 2010 Shadow Robot Company Limited.
//
// FileName:        tactile_edc_ethercat_protocol.h
// Dependencies:
// Processor:       PIC32
// Compiler:        MPLAB® C32
//
//  +------------------------------------------------------------------------+
//  | This file is part of The Shadow Robot PIC32 firmware code base.        |
//  |                                                                        |
//  | It is free software: you can redistribute it and/or modify             |
//  | it under the terms of the GNU General Public License as published by   |
//  | the Free Software Foundation, either version 3 of the License, or      |
//  | (at your option) any later version.                                    |
//  |                                                                        |
//  | It is distributed in the hope that it will be useful,                  |
//  | but WITHOUT ANY WARRANTY; without even the implied warranty of         |
//  | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          |
//  | GNU General Public License for more details.                           |
//  |                                                                        |
//  | You should have received a copy of the GNU General Public License      |
//  | along with this code repository. The text of the license can be found  |
//  | in Pic32/License/gpl.txt. If not, see <http://www.gnu.org/licenses/>.  |
//  +------------------------------------------------------------------------+
//
//
//
//  Doxygen
//  -------
//
//! @file
//!
//! The term "Command" means data going from the ROS PC to the Node on the robot
//! Previously known as "Incoming"
//!
//! The term "Status"  means data going from Node on the robot the to the ROS PC
//! Previously known as "Outgoing"
//!
//!
//! @addtogroup
//

#ifndef TACTILE_EDC_ETHERCAT_PROTOCOL_H_INCLUDED
#define TACTILE_EDC_ETHERCAT_PROTOCOL_H_INCLUDED



//      ---------------
//      TACTILE SENSORS
//      ---------------
#define TACTILE_DATA_LENGTH_BYTES   16
#define TACTILE_DATA_LENGTH_WORDS   (TACTILE_DATA_LENGTH_BYTES/2)

typedef union
{
    int16u  word[TACTILE_DATA_LENGTH_WORDS];                            //!< As yet unspecified
    char    string[TACTILE_DATA_LENGTH_BYTES];
}TACTILE_SENSOR_STATUS;

typedef enum                                                            //! Data you can request from tactile sensors in general
{
    TACTILE_SENSOR_TYPE_WHICH_SENSORS           = 0xFFF9,               //!< Is this a PST, a BioTac, or what? Returns a TACTILE_SENSOR_PROTOCOL_TYPE
    TACTILE_SENSOR_TYPE_SAMPLE_FREQUENCY_HZ     = 0xFFFA,               //!< word[0] = frequency in Hz. currently only used by BioTacs
    TACTILE_SENSOR_TYPE_MANUFACTURER            = 0xFFFB,               //!< e.g. "Shadow" or "Syntouch"
    TACTILE_SENSOR_TYPE_SERIAL_NUMBER           = 0xFFFC,               //!< e.g. "PST3200110190001"
    TACTILE_SENSOR_TYPE_SOFTWARE_VERSION        = 0xFFFD,               //!< e.g. "1825"
    TACTILE_SENSOR_TYPE_PCB_VERSION             = 0xFFFE,               //!< e.g. "FB". Currently only used by BioTacs
    TACTILE_SENSOR_TYPE_RESET_COMMAND           = 0xFFFF                //!< Requesting this causes the tactile sensors to reset if they support it.
}FROM_TACTILE_SENSOR_TYPE;


typedef enum                                                            //! This is the protocol that the palm is using for the tactile sensors.
{
    TACTILE_SENSOR_PROTOCOL_TYPE_INVALID        = 0x0000,               //!< No supported sensors were found.
    TACTILE_SENSOR_PROTOCOL_TYPE_PST3           = 0x0001,
    TACTILE_SENSOR_PROTOCOL_TYPE_BIOTAC_2_3     = 0x0002,

    TACTILE_SENSOR_PROTOCOL_TYPE_CONFLICTING    = 0xFFFF                //!< More than 1 type of sensor is connected to the hand! (Very unlikely to happen)
}TACTILE_SENSOR_PROTOCOL_TYPE;


typedef enum                                                            // Data you can request from PST3s
{
    TACTILE_SENSOR_TYPE_PST3_PRESSURE_TEMPERATURE       = 0x0000,       //!< 0: Pressure.       1: Temperature
    TACTILE_SENSOR_TYPE_PST3_PRESSURE_RAW_ZERO_TRACKING = 0x0002,       //!< 0: Raw pressure    1: Zero tracking
    TACTILE_SENSOR_TYPE_PST3_DAC_VALUE                  = 0x0004        //!< 0: DAC value       1: ----
}FROM_TACTILE_SENSOR_TYPE_PST3;


typedef enum                                                            // Data you can request from BioTacs
{
    TACTILE_SENSOR_TYPE_BIOTAC_INVALID         = 0x0000,
    TACTILE_SENSOR_TYPE_BIOTAC_PDC             = 0x0001,
    TACTILE_SENSOR_TYPE_BIOTAC_TAC             = 0x0002,
    TACTILE_SENSOR_TYPE_BIOTAC_TDC             = 0x0003,
    TACTILE_SENSOR_TYPE_BIOTAC_ELECTRODE_1     = 0x0004,
    TACTILE_SENSOR_TYPE_BIOTAC_ELECTRODE_2     = 0x0005,
    TACTILE_SENSOR_TYPE_BIOTAC_ELECTRODE_3     = 0x0006,
    TACTILE_SENSOR_TYPE_BIOTAC_ELECTRODE_4     = 0x0007,
    TACTILE_SENSOR_TYPE_BIOTAC_ELECTRODE_5     = 0x0008,
    TACTILE_SENSOR_TYPE_BIOTAC_ELECTRODE_6     = 0x0009,
    TACTILE_SENSOR_TYPE_BIOTAC_ELECTRODE_7     = 0x000A,
    TACTILE_SENSOR_TYPE_BIOTAC_ELECTRODE_8     = 0x000B,
    TACTILE_SENSOR_TYPE_BIOTAC_ELECTRODE_9     = 0x000C,
    TACTILE_SENSOR_TYPE_BIOTAC_ELECTRODE_10    = 0x000D,
    TACTILE_SENSOR_TYPE_BIOTAC_ELECTRODE_11    = 0x000E,
    TACTILE_SENSOR_TYPE_BIOTAC_ELECTRODE_12    = 0x000F,
    TACTILE_SENSOR_TYPE_BIOTAC_ELECTRODE_13    = 0x0010,
    TACTILE_SENSOR_TYPE_BIOTAC_ELECTRODE_14    = 0x0011,
    TACTILE_SENSOR_TYPE_BIOTAC_ELECTRODE_15    = 0x0012,
    TACTILE_SENSOR_TYPE_BIOTAC_ELECTRODE_16    = 0x0013,
    TACTILE_SENSOR_TYPE_BIOTAC_ELECTRODE_17    = 0x0014,
    TACTILE_SENSOR_TYPE_BIOTAC_ELECTRODE_18    = 0x0015,
    TACTILE_SENSOR_TYPE_BIOTAC_ELECTRODE_19    = 0x0016,

    FROM_TACTILE_SENSOR_TYPE_BIOTAC_NUM_VALUES = 0x0017
}FROM_TACTILE_SENSOR_TYPE_BIOTAC;


typedef struct
{
    int16u  Pac[2];
    int16u  other_sensor;

    struct
    {
        int8u Pac0         : 1;
        int8u Pac1         : 1;
        int8u other_sensor : 1;
    }data_valid;
    
    int16u  nothing[4];
}TACTILE_SENSOR_BIOTAC_DATA_CONTENTS;


/*
#ifndef NO_STRINGS

    static const char* tactile_sensor_shadow_type_strings[4]  = {   "None",
                                                                    "Pressure Sensor Tactile",
                                                                    "6 Axis"};

    static const char* tactile_sensor_syntouch_type_strings[4] = {  "None",
                                                                    "BioTac 2.3"};



    static const char* tactile_sensor_manufacturer_strings[4] = {   "None",
                                                                    "Shadow Robot Company Ltd.",
                                                                    "Syntouch",
                                                                    "Bielefeld University"};

    static const char* tactile_sensor_generic_info_strings[7] = {   "Invalid",
                                                                    "SVN revision",
                                                                    "Revision is modified",
                                                                    "SVN revision on server at build time",
                                                                    "PCB version",
                                                                    "Part serial number low",
                                                                    "Part serial number high"};

#endif
*/



#endif
