// EddyReadData.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>


const unsigned PC_LENGCONFIGNAME =		12;
const unsigned PC_NUMCHANSETUPS =		24;
const unsigned PC_MIZ43_NUMCHANSETUPS =	32;

struct PC_Channel_Setup
{
	unsigned short	usChannelNum;
	unsigned short	usFrequency;
	unsigned short	usSpan;		/* the scale factor */
	short						sPhase;		/* the rotation angle */
};

void PrintChannelSetup( PC_Channel_Setup a ) {
	printf("\n ChannelNum = %hu ", a.usChannelNum);
	printf(" %lf ", a.usFrequency);
	printf(" %hu ", a.usSpan);		/* the scale factor */
//	printf(" %hu ", a.sPhase);		/* the rotation angle */
}

struct TubeHeader {
	unsigned long	header_code;				/* 0 */
	unsigned long	time;					/* 4 */
	unsigned long	date;					/* 8 */
	char					id[4];					/* 12 */
	char					row[4];					/* 16 */
	char					col[4];					/* 20 */
	char					id_name[4];				/* 24 */
	char					row_name[4];				/* 28 */
	char					col_name[4];				/* 32 */
	unsigned long	start_tape_block;			/* 36 */
	unsigned long	last_tape_block;			/* 40 */

	//This is how Miz43 does it
//	unsigned char	coil_numbers[8];			/* 44 */
//	char					unused2[4];				/* 52 */
	
	//This is how Miz18 does it
	struct freq_and_coil
	{
		unsigned short freq;
		char coils; //coils used, bitmask
	};
	freq_and_coil	freqncoils[4];			// 44 

	unsigned long			delay;					/* 56 */
	char							configuration_name[PC_LENGCONFIGNAME];	/* 60 */
	unsigned long			screen_config;				/* 72 */
	unsigned char			num_channels;				/* 76 */
	unsigned char			bytes_per_slice;			/* 80 */
	unsigned long			left_chart_info;			/* 81 */
	unsigned long			right_chart_info;			/* 82 */
	unsigned long			liz_chart_info;				/* 86 */
	PC_Channel_Setup	channel_setups[PC_MIZ43_NUMCHANSETUPS];	/* 90 */
	unsigned long			number_of_mixers;			/* 346 */
		
	short			recording_path;				/* 350 */
	char			strip_chart_channels[32];		/* 352 */
	char			unused3[2];				/* 384 */
	char			tube_comment[32];			/* 386 */
	char			unused4[26];				/* 418 */
	short			leg;					/* 444 */
	char			unused5;				/* 446 */
	char			chan_names[PC_MIZ43_NUMCHANSETUPS][13];	/* 447 */
	unsigned long	cursor;					/* 863 */
	unsigned long	cursor_hf_width;			/* 867 */
	short			soft_null_x[PC_MIZ43_NUMCHANSETUPS];	/* 871 */
	short			soft_null_y[PC_MIZ43_NUMCHANSETUPS];	/* 935 */
	char			unused6;				/* 999 */
	int				data_type;				/* 1000 */
	int				entry_num;				/* 1004 */
	char			unused7[16];				/* 1008 */
};

int main(int argc, char* argv[])
{
	FILE *fp;

//	fp = fopen("defaulttube_full", "r");
	fp = fopen("DHR002C052I002", "r");
	if( fp == NULL )
		exit(1);

/*
	int					year;
	TubeHeader	h;

	fread(&h, 1, sizeof(TubeHeader), fp);
	
	printf("\n %lX", h.header_code);

	year = h.time / (365*24*3600);
	printf("\n %d  - %ul", year, h.time);

	printf("\n %ul", h.date);

	printf("\n %c%c%c%c", h.id[0], h.id[1], h.id[2], h.id[3]);
	printf("\n %c%c%c%c", h.row[0], h.row[1], h.row[2], h.row[3]);
	printf("\n %c%c%c%c", h.col[0], h.col[1], h.col[2], h.col[3]);

	printf("\n %s", h.configuration_name);
	printf("\n %lu", h.delay );
	printf("\n %lu", h.num_channels );
	printf("\n %lu", h.bytes_per_slice );

	printf("\n Data type = %d", h.data_type);

	printf("\n freq1 = %hu ", h.freqncoils[0].freq );
	printf("\n freq2 = %hu ", h.freqncoils[1].freq );
	printf("\n freq3 = %hu ", h.freqncoils[2].freq );
	printf("\n freq4 = %hu ", h.freqncoils[3].freq );

	for( int i=0; i<24; i++ )
		PrintChannelSetup(h.channel_setups[i]);

	printf("\n Comment = %s ", h.tube_comment);
*/
	char		header[8192];

	return 0;
}

