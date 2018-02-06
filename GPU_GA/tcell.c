//Custom parameters
//Pls touch
#define FULL_SIZE 85
#define TARGET_SIZE 61
#define REDUCED_SIZE 53

//Calculated parameters and aliases
//Pls don't touch
#define POOL_SIZE FULL_SIZE-REDUCED_SIZE

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

struct protein {
	char name[15];
	bool init_val;
	bool final_val;
} PROTEINS[] = {
	///NAME/////////INIT////FINAL///
	{ "AKT",			false,	false	},
	{ "AKT_OFF",		false,	false	},
	{ "AP1",			false,	false	},
};

void run_rule(bool state[], int rule) {
	switch (rule) {
		case AKT:
			state[AKT] = state[PDK1] || state[MTORC2];
			break;
		case AKT_OFF:
			break;
		case AP1:
			state[AP1] = state[FOS_DD] || state[JUN];
			break;
	}
}

