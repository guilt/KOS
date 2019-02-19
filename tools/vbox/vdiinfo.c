#define _LARGEFILE_SOURCE
#define _FILE_OFFSET_BITS 64

#include <stdio.h>

/* #define BIG_ENDIAN */

/* Infomation provided in:
 * http://forums.virtualbox.org/viewtopic.php?t=8046
 */

typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;
typedef char uuid_t[16];

typedef struct vdiheader {
	char headerdesc[64];
	uint32 signature;
	uint16 majorver;
	uint16 minorver;
	uint32 hdrsize;
	uint32 type;
	uint32 flags;
	char desc[256];
	uint32 offsetblocks;
	uint32 offsetdata;
	uint32 cyls;
	uint32 heads;
	uint32 sectors;
	uint32 sectorsize;
	char unused1[4];
	uint64 disksize;
	uint32 blocksize;
	uint32 blockextradata;
	uint32 blocksinhdd;
	uint32 blocksallocated;
	uuid_t uuid;
	uuid_t lastsnapuuid;
	uuid_t linkuuid;
	uuid_t parentuuid;
	char unused2[56];
} vdiheader;

char *vditypestr[] = {
    "NULL",
    "SPARSE",
    "FIXED"
};

void err_usage(char *progname) {
    fprintf(stderr,"Usage is: %s vdi1 vdi2 ...\n", progname);
}

void flipbytes(void *ptr, uint32 size) {
    char *cptr=(char *)ptr;
    uint32 init=0;
    uint32 halfsize=size>>1;
    size--;
    while(init<halfsize) {
	char tmpc=cptr[init];
	cptr[init]=cptr[size];
	cptr[size]=tmpc;
	init++; size--;
    }
}

#define flipuint16(n) flipbytes(n,sizeof(uint16))
#define flipuint32(n) flipbytes(n,sizeof(uint32))
#define flipuint64(n) flipbytes(n,sizeof(uint64))

void readvdiheader(vdiheader *vdih, FILE *in) {
    fread(vdih, sizeof(vdiheader), 1, in);
#ifdef BIG_ENDIAN
    flipuint32(&vdih->signature);
    flipuint16(&vdih->majorver);
    flipuint16(&vdih->minorver);
    flipuint32(&vdih->hdrsize);
    flipuint32(&vdih->type);
    flipuint32(&vdih->flags);
    flipuint32(&vdih->offsetblocks);
    flipuint32(&vdih->offsetdata);
    flipuint32(&vdih->cyls);
    flipuint32(&vdih->heads);
    flipuint32(&vdih->sectors);
    flipuint32(&vdih->sectorsize);
    flipuint64(&vdih->disksize);
    flipuint32(&vdih->blocksize);
    flipuint32(&vdih->blockextradata);
    flipuint32(&vdih->blocksinhdd);
    flipuint32(&vdih->blocksallocated);
#endif //BIG_ENDIAN
}

void printvdiheader(vdiheader *vdih) {
    fprintf(stdout,"Description: %s\n",vdih->headerdesc);
    fprintf(stdout,"Signature: %08x\n",vdih->signature);
    fprintf(stdout,"Version: %u.%u\n",vdih->majorver,vdih->minorver);
    fprintf(stdout,"Header Size: %u\n", vdih->hdrsize);
    fprintf(stdout,"Image Type: %s\n", vditypestr[vdih->type]);
    fprintf(stdout,"Image Flags: %08x\n", vdih->flags);
    fprintf(stdout,"Image Description: %s\n", vdih->desc);
    fprintf(stdout,"Offset Blocks: %u\n", vdih->offsetblocks);
    fprintf(stdout,"Offset Data: %u\n", vdih->offsetdata);
    fprintf(stdout,"Geometry: %uC %uH %uS\n", vdih->cyls, vdih->heads, vdih->sectors);
    fprintf(stdout,"Sector Size: %u\n", vdih->sectorsize);
    fprintf(stdout,"Disk Size: %llu\n", vdih->disksize);
    fprintf(stdout,"Blocks: %u/%u\n", vdih->blocksinhdd, vdih->blocksallocated);
    fprintf(stdout,"Block Size: %u\n", vdih->blocksize);
    fprintf(stdout,"Block Extra Data: %08x\n", vdih->blockextradata);
}

int process(char *vdiname) {
    vdiheader vdih;
    FILE *fvdi=fopen(vdiname,"rb");
    if(!fvdi) {
	fprintf(stderr,"Unable to open: %s\n",vdiname);
	return -1;
    }
    readvdiheader(&vdih,fvdi);
    if(vdih.signature!=0xbeda107f) {
	fprintf(stderr,"Invalid signature in: %s\n",vdiname);
    	fclose(fvdi); fvdi=NULL;
	return -1;
    }
    printvdiheader(&vdih);
    fclose(fvdi); fvdi=NULL;
    return 0;
}

int main(int argc, char *argv[]) {
    int i=1;
    if(argc<2) {
	err_usage(argv[0]);
	return -1;
    }
    for(; i<argc; ++i) {
	process(argv[i]);
    }
    return 0;
}
