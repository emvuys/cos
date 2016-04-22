#include <stdio.h>
#include <stdlib.h>
#include "filetype.h"
#include "fileSystem.h"


FileDesc* buildEFs(FileDesc* pfileList, u1* fids, u1 len) {
	u2 fid;
	u1 totolLen = len;
	while(len --) {
		
		switch (fid) {
			case EF_ACC:
			case EF_ACL:
			case EF_AD:
			case EF_ARR:
			case EF_ARR_SUB:
			case EF_DIR:
			case EF_ECC:
			case EF_EHPLMN:
			case EF_EST:
			case EF_FPLMN:
			case EF_HPLMNwAcT:
			case EF_HPPLMN:
			case EF_ICCID:
			case EF_IMSI:
			case EF_Kc:
			case EF_KcGPRS:
			case EF_Keys:
			case EF_KeysPS:
			case EF_LI:
			case EF_LOCI:
			case EF_NETPAR:
			case EF_OPL:
			case EF_OPLMNwAcT:
			case EF_PL:
			case EF_PLMNwAcT:
			case EF_PNN:
			case EF_PSLOCI:
			case EF_SPDI:
			case EF_SPN:
			case EF_START_HFN:
			case EF_THRESHOLD:
			case EF_UST:
				break;	
		}
	}
}

