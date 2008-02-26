/**
 *  @file    femparm.c
 *  @ingroup FEMparm
 *  @author  Nathan Baker
 *  @brief   Class FEMparm methods
 *  @version $Id$
 *  @attention
 *  @verbatim
 *
 * APBS -- Adaptive Poisson-Boltzmann Solver
 *
 * Nathan A. Baker (baker@biochem.wustl.edu)
 * Dept. of Biochemistry and Molecular Biophysics
 * Center for Computational Biology
 * Washington University in St. Louis
 *
 * Additional contributing authors listed in the code documentation.
 *
 * Copyright (c) 2002-2007.  Washington University in St. Louis.
 * All Rights Reserved.
 * Portions Copyright (c) 1999-2002.  The Regents of the University of
 * California.  
 * Portions Copyright (c) 1995.  Michael Holst.
 *
 * This file is part of APBS.
 *
 * APBS is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * APBS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with APBS; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 *
 * Linking APBS statically or dynamically with other modules is making a
 * combined work based on APBS. Thus, the terms and conditions of the GNU
 * General Public License cover the whole combination.
 * 
 * SPECIAL GPL EXCEPTION
 * In addition, as a special exception, the copyright holders of APBS
 * give you permission to combine the APBS program with free software
 * programs and libraries that are released under the GNU LGPL or with
 * code included in releases of ISIM, Ion Simulator Interface, PMV, PyMOL
 * SMOL, VMD, and Vision. Such combined software may be linked with APBS and 
 * redistributed together in original or modified form as mere aggregation
 * without requirement that the entire work be under the scope of the GNU 
 * General Public License. This special exception permission is also extended
 * to any software listed in the SPECIAL GPL EXCEPTION clauses by the PMG,
 * FEtk, MC, or MALOC libraries.
 * 
 * Note that people who make modified versions of APBS are not obligated
 * to grant this special exception for their modified versions; it is
 * their choice whether to do so. The GNU General Public License gives
 * permission to release a modified version without this exception; this
 * exception also makes it possible to release a modified version which
 * carries forward this exception.
 *
 * @endverbatim
 */


#include "apbscfg.h"
#include "apbs/femparm.h"

VEMBED(rcsid="$Id$")

#if !defined(VINLINE_MGPARM)

#endif /* if !defined(VINLINE_MGPARM) */

VPUBLIC FEMparm* FEMparm_ctor(FEMparm_CalcType type) {

    /* Set up the structure */
    FEMparm *thee = VNULL;
    thee = Vmem_malloc(VNULL, 1, sizeof(FEMparm));
    VASSERT( thee != VNULL);
    VASSERT( FEMparm_ctor2(thee, type) );

    return thee;
}

VPUBLIC int FEMparm_ctor2(FEMparm *thee, FEMparm_CalcType type) {

    if (thee == VNULL) return 0;

    thee->parsed = 0;
    thee->type = type;
    thee->settype = 1;

    thee->setglen = 0;
    thee->setetol = 0;
    thee->setekey = 0;
    thee->setakeyPRE = 0;
    thee->setakeySOLVE = 0;
    thee->settargetNum = 0;
    thee->settargetRes = 0;
    thee->setmaxsolve = 0;
    thee->setmaxvert = 0;
	thee->useMesh = 0;

    return 1; 
}

VPUBLIC void FEMparm_copy(
						  FEMparm *thee,
						  FEMparm *source
						  ) {
	
	int i;
	
	thee->parsed = source->parsed;
	thee->type = source->type;
	thee->settype = source->settype;
	for (i=0; i<3; i++) thee->glen[i] = source->glen[i];
	thee->setglen = source->setglen;
	thee->etol = source->etol;
	thee->setetol = source->setetol;
	thee->ekey = source->ekey;
	thee->setekey = source->setekey;
	thee->akeyPRE = source->akeyPRE;
	thee->setakeyPRE = source->setakeyPRE;
	thee->akeySOLVE = source->akeySOLVE;
	thee->setakeySOLVE = source->setakeySOLVE;
	thee->targetNum = source->targetNum;
	thee->settargetNum = source->settargetNum;
	thee->targetRes = source->targetRes;
	thee->settargetRes = source->settargetRes;
	thee->maxsolve = source->maxsolve;
	thee->setmaxsolve = source->setmaxsolve;
	thee->maxvert = source->maxvert;
	thee->setmaxvert = source->setmaxvert;
	thee->pkey = source->pkey;
	thee->useMesh = source->useMesh;
	thee->meshID = source->meshID;
}

VPUBLIC void FEMparm_dtor(FEMparm **thee) {
    if ((*thee) != VNULL) {
        FEMparm_dtor2(*thee);
        Vmem_free(VNULL, 1, sizeof(FEMparm), (void **)thee);
        (*thee) = VNULL;
    }
}

VPUBLIC void FEMparm_dtor2(FEMparm *thee) { ; }

VPUBLIC int FEMparm_check(FEMparm *thee) { 

    int rc;
    rc = 1;

    if (!thee->parsed) {
        Vnm_print(2, "FEMparm_check:  not filled!\n");
        return 0;
    }
    if (!thee->settype) {
        Vnm_print(2, "FEMparm_check:  type not set!\n");
        rc = 0;
    }
    if (!thee->setglen) {
        Vnm_print(2, "FEMparm_check:  glen not set!\n");
        rc = 0;
    }
    if (!thee->setetol) {
        Vnm_print(2, "FEMparm_check:  etol not set!\n");
        rc = 0;
    }
    if (!thee->setekey) {
        Vnm_print(2, "FEMparm_check:  ekey not set!\n");
        rc = 0;
    }
    if (!thee->setakeyPRE) {
        Vnm_print(2, "FEMparm_check:  akeyPRE not set!\n");
        rc = 0;
    }
    if (!thee->setakeySOLVE) {
        Vnm_print(2, "FEMparm_check:  akeySOLVE not set!\n");
        rc = 0;
    }
    if (!thee->settargetNum) {
        Vnm_print(2, "FEMparm_check:  targetNum not set!\n");
        rc = 0;
    }
    if (!thee->settargetRes) {
        Vnm_print(2, "FEMparm_check:  targetRes not set!\n");
        rc = 0;
    }
    if (!thee->setmaxsolve) {
        Vnm_print(2, "FEMparm_check:  maxsolve not set!\n");
        rc = 0;
    }
    if (!thee->setmaxvert) {
        Vnm_print(2, "FEMparm_check:  maxvert not set!\n");
        rc = 0;
    }

    return rc;
}

VPRIVATE Vrc_Codes FEMparm_parseDOMAINLENGTH(FEMparm *thee, Vio *sock) {

    int i;
    double tf;
    char tok[VMAX_BUFSIZE];

    for (i=0; i<3; i++) {
        VJMPERR1(Vio_scanf(sock, "%s", tok) == 1);
        if (sscanf(tok, "%lf", &tf) == 0) {
            Vnm_print(2, "parseFE:  Read non-double (%s) while parsing \
DOMAINLENGTH keyword!\n", tok);
            return VRC_FAILURE;
        } 
        thee->glen[i] = tf;
    }
    thee->setglen = 1;
    return VRC_SUCCESS;
VERROR1:
    Vnm_print(2, "parseFE:  ran out of tokens!\n");
    return VRC_FAILURE;

}

VPRIVATE Vrc_Codes FEMparm_parseETOL(FEMparm *thee, Vio *sock) {

    double tf;
    char tok[VMAX_BUFSIZE];

    VJMPERR1(Vio_scanf(sock, "%s", tok) == 1);
    if (sscanf(tok, "%lf", &tf) == 0) {
        Vnm_print(2, "parseFE:  Read non-double (%s) while parsing \
ETOL keyword!\n", tok);
        return VRC_FAILURE;
    }
    thee->etol = tf;
    thee->setetol = 1;
    return VRC_SUCCESS;
VERROR1:
    Vnm_print(2, "parseFE:  ran out of tokens!\n");
    return VRC_FAILURE;


}

VPRIVATE Vrc_Codes FEMparm_parseEKEY(FEMparm *thee, Vio *sock) {

    char tok[VMAX_BUFSIZE];
    Vrc_Codes vrc = VRC_FAILURE;

    VJMPERR1(Vio_scanf(sock, "%s", tok) == 1);
    if (Vstring_strcasecmp(tok, "simp") == 0) {
        thee->ekey = FET_SIMP;
        thee->setekey = 1;
        vrc = VRC_SUCCESS;
    } else if (Vstring_strcasecmp(tok, "glob") == 0) {
        thee->ekey = FET_GLOB;
        thee->setekey = 1;
        vrc = VRC_SUCCESS;
    } else if (Vstring_strcasecmp(tok, "frac") == 0) {
        thee->ekey = FET_FRAC;
        thee->setekey = 1;
        vrc = VRC_SUCCESS;
    } else {
        Vnm_print(2, "parseFE:  undefined value (%s) for ekey!\n", tok);
        vrc = VRC_FAILURE;
    }

    return vrc;
VERROR1:
    Vnm_print(2, "parseFE:  ran out of tokens!\n");
    return VRC_FAILURE;

}

VPRIVATE Vrc_Codes FEMparm_parseAKEYPRE(FEMparm *thee, Vio *sock) {

    char tok[VMAX_BUFSIZE];
    Vrc_Codes vrc = VRC_FAILURE;

    VJMPERR1(Vio_scanf(sock, "%s", tok) == 1);
    if (Vstring_strcasecmp(tok, "unif") == 0) {
        thee->akeyPRE = FRT_UNIF;
        thee->setakeyPRE = 1;
        vrc =  VRC_SUCCESS;
    } else if (Vstring_strcasecmp(tok, "geom") == 0) {
        thee->akeyPRE = FRT_GEOM;
        thee->setakeyPRE = 1;
        vrc =  VRC_SUCCESS;
    } else {
        Vnm_print(2, "parseFE:  undefined value (%s) for akeyPRE!\n", tok);
        vrc =  VRC_FAILURE;
    }

    return vrc;

VERROR1:
    Vnm_print(2, "parseFE:  ran out of tokens!\n");
    return VRC_FAILURE;

}

VPRIVATE Vrc_Codes FEMparm_parseAKEYSOLVE(FEMparm *thee, Vio *sock) {

    char tok[VMAX_BUFSIZE];
    int vrc = VRC_FAILURE;

    VJMPERR1(Vio_scanf(sock, "%s", tok) == 1);
    if (Vstring_strcasecmp(tok, "resi") == 0) {
        thee->akeySOLVE = FRT_RESI;
        thee->setakeySOLVE = 1;
        vrc =  VRC_SUCCESS;
    } else if (Vstring_strcasecmp(tok, "dual") == 0) {
        thee->akeySOLVE = FRT_DUAL;
        thee->setakeySOLVE = 1;
        vrc =  VRC_SUCCESS;
    } else if (Vstring_strcasecmp(tok, "loca") == 0) {
        thee->akeySOLVE = FRT_LOCA;
        thee->setakeySOLVE = 1;
        vrc =  VRC_SUCCESS;
    } else {
        Vnm_print(2, "parseFE:  undefined value (%s) for akeyPRE!\n", tok);
        vrc =  VRC_FAILURE;
    }

    return vrc;
VERROR1:
    Vnm_print(2, "parseFE:  ran out of tokens!\n");
    return VRC_SUCCESS;

}

VPRIVATE Vrc_Codes FEMparm_parseTARGETNUM(FEMparm *thee, Vio *sock) {

    char tok[VMAX_BUFSIZE];
    int ti;

    VJMPERR1(Vio_scanf(sock, "%s", tok) == 1);
    if (sscanf(tok, "%d", &ti) == 0) {
        Vnm_print(2, "parseFE:  read non-int (%s) for targetNum!\n", tok);
        return VRC_FAILURE;
    }
    thee->targetNum = ti;
    thee->settargetNum = 1;
    return VRC_SUCCESS;
VERROR1:
    Vnm_print(2, "parseFE:  ran out of tokens!\n");
    return VRC_FAILURE;

}

VPRIVATE Vrc_Codes FEMparm_parseTARGETRES(FEMparm *thee, Vio *sock) {

    char tok[VMAX_BUFSIZE];
    double tf;

    VJMPERR1(Vio_scanf(sock, "%s", tok) == 1);
    if (sscanf(tok, "%lf", &tf) == 0) {
        Vnm_print(2, "parseFE:  read non-double (%s) for targetNum!\n", 
          tok);
        return VRC_FAILURE;
    }
    thee->targetRes = tf;
    thee->settargetRes = 1;
    return VRC_SUCCESS;
VERROR1:
    Vnm_print(2, "parseFE:  ran out of tokens!\n");
    return VRC_FAILURE;

}

VPRIVATE Vrc_Codes FEMparm_parseMAXSOLVE(FEMparm *thee, Vio *sock) {

    char tok[VMAX_BUFSIZE];
    int ti;

    VJMPERR1(Vio_scanf(sock, "%s", tok) == 1);
    if (sscanf(tok, "%d", &ti) == 0) {
        Vnm_print(2, "parseFE:  read non-int (%s) for maxsolve!\n", tok);
        return VRC_FAILURE;
    }
    thee->maxsolve = ti;
    thee->setmaxsolve = 1;
    return VRC_SUCCESS;
VERROR1:
    Vnm_print(2, "parseFE:  ran out of tokens!\n");
    return VRC_FAILURE;

}

VPRIVATE Vrc_Codes FEMparm_parseMAXVERT(FEMparm *thee, Vio *sock) {

    char tok[VMAX_BUFSIZE];
    int ti;

    VJMPERR1(Vio_scanf(sock, "%s", tok) == 1);
    if (sscanf(tok, "%d", &ti) == 0) {
        Vnm_print(2, "parseFE:  read non-int (%s) for maxvert!\n", tok);
        return VRC_FAILURE;
    }
    thee->maxvert = ti;
    thee->setmaxvert = 1;
    return VRC_SUCCESS;
	
VERROR1:
    Vnm_print(2, "parseFE:  ran out of tokens!\n");
    return VRC_FAILURE;

}

VPRIVATE Vrc_Codes FEMparm_parseUSEMESH(FEMparm *thee, Vio *sock) {
    char tok[VMAX_BUFSIZE];
    int ti;
	
    VJMPERR1(Vio_scanf(sock, "%s", tok) == 1);
	if (sscanf(tok, "%d", &ti) == 0) {
        Vnm_print(2, "parseFE:  read non-int (%s) for usemesh!\n", tok);
        return VRC_FAILURE;
    }	
	thee->useMesh = 1;
	thee->meshID = ti;
	
	return VRC_SUCCESS;
	
VERROR1:
	Vnm_print(2, "parsePBE:  ran out of tokens!\n");
	return VRC_FAILURE;
}


VPUBLIC Vrc_Codes FEMparm_parseToken(FEMparm *thee, char tok[VMAX_BUFSIZE],
  Vio *sock) {

    int i, ti;
    double tf;

    if (thee == VNULL) {
        Vnm_print(2, "parseFE:  got NULL thee!\n");
        return VRC_FAILURE;
    }

    if (sock == VNULL) {
        Vnm_print(2, "parseFE:  got NULL socket!\n");
        return VRC_FAILURE;
    }

    if (Vstring_strcasecmp(tok, "domainLength") == 0) {
        return FEMparm_parseDOMAINLENGTH(thee, sock);
    } else if (Vstring_strcasecmp(tok, "etol") == 0) {
        return FEMparm_parseETOL(thee, sock);
    } else if (Vstring_strcasecmp(tok, "ekey") == 0) {
        return FEMparm_parseEKEY(thee, sock);
    } else if (Vstring_strcasecmp(tok, "akeyPRE") == 0) {
        return FEMparm_parseAKEYPRE(thee, sock);
    } else if (Vstring_strcasecmp(tok, "akeySOLVE") == 0) {
        return FEMparm_parseAKEYSOLVE(thee, sock);
    } else if (Vstring_strcasecmp(tok, "targetNum") == 0) {
        return FEMparm_parseTARGETNUM(thee, sock);
    } else if (Vstring_strcasecmp(tok, "targetRes") == 0) {
        return FEMparm_parseTARGETRES(thee, sock);
    } else if (Vstring_strcasecmp(tok, "maxsolve") == 0) {
        return FEMparm_parseMAXSOLVE(thee, sock);
    } else if (Vstring_strcasecmp(tok, "maxvert") == 0) {
        return FEMparm_parseMAXVERT(thee, sock);
    } else if (Vstring_strcasecmp(tok, "usemesh") == 0) {
        return FEMparm_parseUSEMESH(thee, sock);
    }

    return VRC_WARNING;

}
