//Custom parameters
//Pls touch
#define FULL_SIZE 85
#define TARGET_RULES 61
#define REDUCED_RULES 53
#define NUM_INITIAL_CONDITIONS 2

//Calculated parameters and aliases
//Pls don't touch
#define POOL_SIZE FULL_SIZE-REDUCED_SIZE
#define NOT(num) (num ^ 1)

//REDUCED MODEL PROTEINS
#define AKT			0
#define AKT_OFF		1
#define AP1			2
#define CD122		3
#define CD25		4
#define CD28		5
#define FOS			6
#define FOS_D		7
#define FOS_DD		8
#define FOS_DDD		9
#define FOXP3		10
#define IL2			11
#define IL2_EX		12
#define IL2R		13
#define JAK3		14
#define JNK			15
#define MEK2		16
#define MKK7		17
#define MTOR		18
#define MTOR_D		19
#define MTOR_DD		20
#define MTOR_DDD	21
#define MTOR_DDDD	22
#define MTORC1		23
#define MTORC1_D	24
#define MTORC1_OFF	25
#define MTORC2		26
#define MTORC2_D	27
#define MTORC2_DD	28
#define NFAT		29
#define NFAT_OFF	30
#define NFKAPPAB	31
#define PI3K		32
#define PI3K_HIGH	33
#define PI3K_LOW	34
#define PIP3		35
#define PIP3_HIGH	36
#define PIP3_LOW	37
#define PKCTHETA	38
#define PS6			39
#define PTEN		40
#define RAS			41
#define S6K1		42
#define SMAD3		43
#define STAT5		44
#define STAT5_D		45
#define STAT5_DD	46
#define STAT5_DDD	47
#define TAK1		48
#define TCR			49
#define TCR_HIGH	50
#define TCR_LOW		51
#define TSC			52

//POOL PROTEINS
#define H1			53
#define U1			54
#define CA			55
#define D1			56
#define S1			57
#define CD132		58
#define H2			59
#define U2			60
#define D2			61
#define ERK			62
#define S2			63
#define H3			64
#define JUN			65
#define U3			66
#define D3			67
#define S3			68
#define H4			69
#define PDK1		70
#define U4			71
#define D4			72
#define S4			73
#define RAF			74
#define H5			75
#define H6			76
#define RHEB		77
#define H7			78
#define H8			79
#define H9			80
#define TGFBETA		81
#define H10			82
#define D5			83
#define D6			84

struct Proteins {
	char name[15];
	bool init_val[NUM_INITIAL_CONDITIONS];
	bool final_val[NUM_INITIAL_CONDITIONS];
} PROTEIN[] = {
	///NAME///////////INIT/////FINAL///
	{ "AKT",			{ 0, 0 } },
	{ "AKT_OFF",		{ 0, 0 } },
	{ "AP1",			{ 0, 0 } },
	{ "CA",			{ 0, 0 } },
	{ "CD122",		{ 1, 1 } },
	{ "CD132",		{ 1, 1 } },
	{ "CD25",		{ 0, 0 } },
	{ "CD28",		{ 1, 1 } },
	{ "ERK",			{ 0, 0 } },
	{ "FOS",			{ 0, 0 } },
	{ "FOS_D",		{ 0, 0 } },
	{ "FOS_DD",		{ 0, 0 } },
	{ "FOS_DDD",		{ 0, 0 } },
	{ "FOXP3",		{ 0, 0 } },
	{ "IL2",			{ 0, 0 } },
	{ "IL2_EX",		{ 0, 0 } },
	{ "IL2R",		{ 0, 0 } },
	{ "JAK3",		{ 0, 0 } },
	{ "JNK",			{ 0, 0 } },
	{ "JUN",			{ 0, 0 } },
	{ "MEK2",		{ 0, 0 } },
	{ "MKK7",		{ 0, 0 } },
	{ "MTOR",		{ 0, 0 } },
	{ "MTOR_D",		{ 0, 0 } },
	{ "MTOR_DD",		{ 0, 0 } },
	{ "MTOR_DDD",	{ 0, 0 } },
	{ "MTOR_DDDD",	{ 0, 0 } },
	{ "MTORC1",		{ 0, 0 } },
	{ "MTORC1_D",	{ 0, 0 } },
	{ "MTORC1_OFF",	{ 0, 0 } },
	{ "MTORC2",		{ 0, 0 } },
	{ "MTORC2_D",	{ 0, 0 } },
	{ "MTORC2_DD",	{ 0, 0 } },
	{ "NFAT",		{ 0, 0 } },
	{ "NFAT_OFF",	{ 0, 0 } },
	{ "NFKAPPAB",	{ 0, 0 } },
	{ "PDK1",		{ 0, 0 } },
	{ "PI3K",		{ 0, 0 } },
	{ "PI3K_HIGH",	{ 0, 0 } },
	{ "PI3K_LOW",	{ 0, 0 } },
	{ "PIP3",		{ 0, 0 } },
	{ "PIP3_HIGH",	{ 0, 0 } },
	{ "PIP3_LOW",	{ 0, 0 } },
	{ "PKCTHETA",	{ 0, 0 } },
	{ "PS6",			{ 0, 0 } },
	{ "PTEN",		{ 1, 1 } },
	{ "RAF",			{ 0, 0 } },
	{ "RAS",			{ 0, 0 } },
	{ "RHEB",		{ 0, 0 } },
	{ "S6K1",		{ 0, 0 } },
	{ "SMAD3",		{ 0, 0 } },
	{ "STAT5",		{ 0, 0 } },
	{ "STAT5_D",		{ 0, 0 } },
	{ "STAT5_DD",	{ 0, 0 } },
	{ "STAT5_DDD",	{ 0, 0 } },
	{ "TAK1",		{ 0, 0 } },
	{ "TCR",			{ 0, 0 } },
	{ "TCR_HIGH",	{ 1, 0 } },
	{ "TCR_LOW",		{ 0, 1 } },
	{ "TGFBETA",		{ 0, 0 } },
	{ "TSC",			{ 1, 1 } },
	{ "H1",			{ 0, 0 } },
	{ "U1",			{ 1, 1 } },
	{ "D1",			{ 0, 0 } },
	{ "S1",			{ 0, 0 } },
	{ "H2",			{ 0, 0 } },
	{ "U2",			{ 1, 1 } },
	{ "D2",			{ 0, 0 } },
	{ "S2",			{ 0, 0 } },
	{ "H3",			{ 0, 0 } },
	{ "U3",			{ 1, 1 } },
	{ "D3",			{ 0, 0 } },
	{ "S3",			{ 0, 0 } },
	{ "H4",			{ 0, 0 } },
	{ "U4",			{ 1, 1 } },
	{ "D4",			{ 0, 0 } },
	{ "S4",			{ 0, 0 } },
	{ "H5",			{ 0, 0 } },
	{ "H6",			{ 0, 0 } },
	{ "H7",			{ 0, 0 } },
	{ "H8",			{ 0, 0 } },
	{ "H9",			{ 0, 0 } },
	{ "H10",			{ 0, 0 } },
	{ "D5",			{ 0, 0 } },
	{ "D6",			{ 0, 0 } },


	//TODO FINISH
};

void initialize_state(char *state, int init_condition_num) {
	for (int i = 0; i < FULL_SIZE; i++) {
		if (state[i] != -1) {
			state[i] = PROTEIN[i].init_val[init_condition_num];
		}
	}
}

void run_rule(char *state, int rule) {
	switch (rule) {
		case AKT:
			if (state[PDK1] != -1) {
				state[AKT] = state[PDK1] & state[MTORC2] & NOT(state[AKT_OFF]);
			}
			return;
		case AKT_OFF:
			return;
		case AP1:
			if (state[AP1] != -1) {
				state[AP1] = state[FOS_DD] & state[JUN];
			}
			return;
		case CA:
			state[CA] = state[TCR];
			return;
		case CD122:
			return;
		case CD132:
			return;
		case CD25:
			state[CD25] = state[FOXP3] | (state[AP1] & state[NFAT] & state[NFKAPPAB]) | state[JUN];
			return;
		case CD28:
			return;
		case ERK:
			if (state[S1] != -1) {
				state[ERK] = state[MEK2] & state[S1];
			}
			else if (state[S1] == -1) {
				state[ERK] = state[MEK2];
			}
			return;
		case FOS:
			if (state[ERK] != -1) {
				state[FOS] = state[ERK];
			}
			return;
		case FOS_D:
			state[FOS_D] = state[FOS];
			return;
		case FOS_DD:
			state[FOS_DD] = state[FOS_D];
			return;
		case FOS_DDD:
			return;
		case FOXP3:
			if (state[S4] != -1) {
				state[FOXP3] = ((NOT(state[MTOR_DD]) & state[STAT5]) | (state[NFAT] & state[SMAD3])) & NOT(state[S4]);
			}
			else if (state[S4] == -1) {
				state[FOXP3] = (NOT(state[MTOR_DD]) & state[STAT5]) | (state[NFAT] & state[SMAD3]);
			}
			return;
		case IL2:
			state[IL2] = ((state[AP1] & state[NFAT] & state[NFKAPPAB]) | IL2) & NOT(state[FOXP3]);
			return;
		case IL2_EX:
			state[IL2_EX] = state[IL2] | state[IL2_EX];
			return;
		case IL2R:
			state[IL2R] = state[CD25] & state[CD122] & state[CD132];
			return;
		case JAK3:
			state[JAK3] = state[IL2R] & state[IL2_EX];
			return;
		case JNK:
			state[JNK] = state[MKK7];
			return;
		case JUN:
			state[JUN] = state[JNK];
			return;
		case MEK2:
			if (state[MEK2] != -1) {
				state[MEK2] = state[RAF];
			}
			return;
		case MKK7:
			state[MKK7] = state[TAK1];
			return;
		case MTOR:
			state[MTOR] = state[MTORC1_D] & state[MTORC2_D];
			return;
		case MTOR_D:
			state[MTOR_D] = state[MTOR];
			return;
		case MTOR_DD:
			state[MTOR_DD] = state[MTOR_D];
			return;
		case MTOR_DDD:
			return;
		case MTOR_DDDD:
			return;
		case MTORC1:
			if (state[RHEB] != -1) {
				state[MTORC1] = state[RHEB] & NOT(MTORC1_OFF);
			}
			return;
		case MTORC1_D:
			state[MTORC1_D] = state[MTORC1];
			return;
		case MTORC1_OFF:
			return;
		case MTORC2:
			state[MTORC2] = state[PI3K_HIGH] | (state[PI3K_LOW] & NOT(state[S6K1]));
			return;
		case MTORC2_D:
			state[MTORC2_D] = state[MTORC2];
			return;
		case MTORC2_DD:
			return;
		case NFAT:
			if (state[CA] != -1) {
				state[NFAT] = state[CA] & NOT(state[NFAT_OFF]);
			}
			return;
		case NFAT_OFF:
			return;
		case NFKAPPAB:
			if (state[S2] != -1) {
				state[NFKAPPAB] = state[AKT] | state[PKCTHETA] | state[U2];
			}
			else if (state[S2] == -1) {
				state[NFKAPPAB] = state[AKT] | state[PKCTHETA];
			}
			return;
		case PDK1:
			state[PDK1] = state[PIP3];
			return;
		case PI3K:
			state[PI3K] = state[PI3K_LOW] | state[PI3K_HIGH];
			return;
		case PI3K_HIGH:
			state[PI3K_HIGH] = (state[TCR_HIGH] & state[CD28]) | (state[PI3K_HIGH] & state[IL2_EX] & state[IL2R]);
			return;
		case PI3K_LOW:
			state[PI3K_LOW] = (state[TCR_LOW] & state[CD28]) | (state[PI3K_LOW] & state[IL2_EX] & state[IL2R]);
			return;
		case PIP3:
			state[PIP3] = state[PIP3_LOW] | state[PIP3_HIGH];
			return;
		case PIP3_HIGH:
			state[PIP3_HIGH] = state[PI3K_HIGH] & NOT(state[PTEN]);
			return;
		case PIP3_LOW:
			state[PIP3_LOW] = state[PI3K_LOW] & NOT(state[PTEN]);
			return;
		case PKCTHETA:
			state[PKCTHETA] = state[TCR_HIGH] | (state[TCR_LOW] & state[CD28] & state[MTORC2]);
			return;
		case PS6:
			state[PS6] = state[S6K1];
			return;
		case PTEN:
			state[PTEN] = (state[FOXP3] & NOT(state[TCR_HIGH])) | (state[PTEN] & NOT(state[TCR_HIGH]));
			return;
		case RAF:
			if (state[U1] != -1) {
				state[RAF] = state[RAS] & NOT(state[U1]);
			}
			else if (state[U1] == -1) {
				state[RAF] = state[RAS];
			}
			return;
		case RAS:
			state[RAS] = (state[TCR] & state[CD28]) | (state[RAS] & state[IL2_EX] & state[IL2R]);
			return;
		case RHEB:
			state[RHEB] = NOT(state[TSC]);
			return;
		case S6K1:
			if (state[S3] != -1 && state[U4] != -1) {
				state[S6K1] = (state[MTORC1] | state[S3]) & NOT(state[U4]);
			}
			else if (state[S3] == -1 && state[U4] != -1) {
				state[S6K1] = state[MTORC1] & NOT(state[U4]);
			}
			else if (state[S3] != -1 && state[U4] == -1) {
				state[S6K1] = state[MTORC1] | state[S3];
			}
			else if (state[S3] == -1 && state[U4] == -1) {
				state[S6K1] = state[MTORC1];
			}
			return;
		case SMAD3:
			if (state[TGFBETA] != -1) {
				state[SMAD3] = state[TGFBETA];
			}
			return;
		case STAT5:
			if (state[S2] != -1) {
				state[STAT5] = state[JAK3] & NOT(state[S2]);
			}
			else if (state[S2] == -1) {
				state[STAT5] = state[JAK3];
			}
			return;
		case STAT5_D:
			state[STAT5_D] = state[STAT5];
			return;
		case STAT5_DD:
			return;
		case STAT5_DDD:
			return;
		case TAK1:
			if (state[U3] != -1) {
				state[TAK1] = state[PKCTHETA] | state[U3];
			}
			else if (state[U3] == -1) {
				state[TAK1] = state[PKCTHETA];
			}
			return;
		case TCR:
			state[TCR] = state[TCR_LOW] | state[TCR_HIGH];
			return;
		case TCR_HIGH:
			return;
		case TCR_LOW:
			return;
		case TGFBETA:
			return;
		case TSC:
			state[TSC] = NOT(state[AKT]);
			return;
		case H1:
			return;
		case U1:
			return;
		case D1:
			state[D1] = state[AP1];
			return;
		case S1:
			state[S1] = state[MKK7];
			return;
		case H2:
			if (state[H1] != -1) {
				state[H2] = state[H1];
			}
			return;
		case U2:
			return;
		case D2:
			state[D2] = NOT(state[PS6]);
			return;
		case S2:
			state[S2] = state[NFKAPPAB];
			return;
		case H3:
			return;
		case U3:
			return;
		case D3:
			state[D3] = state[SMAD3];
			return;
		case S3:
			state[S3] = state[AKT];
			return;
		case H4:
			if (state[H3] != -1) {
				state[H4] = state[H3];
			}
			return;
		case U4:
			return;
		case D4:
			if (state[RAF] != -1) {
				state[D4] = state[RAF];
			}
			return;
		case S4:
			state[S4] = state[IL2];
			return;
		case H5:
			return;
		case H6:
			if (state[H5] != -1) {
				state[H6] = state[H5];
			}
			return;
		case H7:
			return;
		case H8:
			if (state[H7] != -1) {
				state[H8] = state[H7];
			}
			return;
		case H9:
			return;
		case H10:
			if (state[H9] != -1) {
				state[H10] = NOT(state[H9]);
			}
			return;
		case D5:
			state[D5] = NOT(state[IL2]);
			return;
		case D6:
			state[D6] = state[FOXP3];
			return;
	}
}

int calculate_error(double *avg_state, int init_condition_num) {
	int error = 0;

	if (init_condition_num == 0) { //TCR_HIGH
		if (avg_state[IL2] < 0.95) error += 1;
		if (avg_state[FOXP3] > 0.05) error += 1;
		if (avg_state[PTEN] > 0.05) error += 1;
		if (avg_state[AKT] < 0.95) error += 1;
		if (avg_state[MTORC1] < 0.95) error += 1;
	}
	else if (init_condition_num == 1) { //TCR_LOW
		if (avg_state[IL2] > 0.05) error += 1;
		if (avg_state[FOXP3] < 0.95) error += 1;
		if (avg_state[PTEN] < 0.95) error += 1;
		if (avg_state[AKT] > 0.05) error += 1;
		if (avg_state[MTORC1] > 0.05) error += 1;
	}
	
	return error;
}

