/*                          =======================
============================   C/C++ HEADER FILE   ============================
                            =======================                       *//**
  UpdateClassVirt.h

  Created by Onno Dirkzwager on 10.02.2019.
  Copyright (c) 2019 IOTAppStory. All rights reserved.

*///===========================================================================

#ifndef __UpdateClassVirt_h__
#define __UpdateClassVirt_h__

/*---------------------------------------------------------------------------*/
/*                                    INCLUDES                               */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                            DEFINITIONS AND MACROS                         */
/*---------------------------------------------------------------------------*/

#define U_FLASH       0
#define U_FILESYSTEM  100
#define U_AUTH        200
#define U_NEXTION     300

/*---------------------------------------------------------------------------*/
/*                        TYPEDEFS, CLASSES AND STRUCTURES                   */
/*---------------------------------------------------------------------------*/

/*                          =======================
============================   CLASS DEFINITION    ============================
                            =======================                       *//**
  UpdateClassVirt.

*//*=========================================================================*/
class UpdateClassVirt {
public:
    virtual bool prepareUpdate(uint32_t upd_size, String &upd_md5, uint16_t command);

    virtual bool update(uint8_t *file_buf, size_t buf_size);

    virtual bool end(void);

    virtual void sm(String *statusMessage);
};

/*---------------------------------------------------------------------------*/
/*                                GLOBAL VARIABLES                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                                    EOF                                    */
/*---------------------------------------------------------------------------*/
#endif // __UpdateClassVirt_h__
