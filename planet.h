#include <math.h>

#define sun 		0
#define mercury 	8
#define venus 		16
#define earth 		24
#define mars 		32
#define jupiter		40
#define saturn		48
#define uranus		56
#define neptune		64

#define OFFS_X			0
#define OFFS_Y			1
#define OFFS_MASS		2
#define OFFS_DISTANCE	3
#define OFFS_PERIOD		4
#define OFFS_GRAVITY	5
#define OFFS_RADIUS		6

#define G			1000.0
#define SOLsqr		(2.0)

#define pmass(x)	sqrt(sqrt(x*100.0))*1.5
#define pdis(x)		(x/57900.0)
#define pper(x)		(x*0.05)
#define pgrav(x)	((2.0*G*(x))*0.001)
#define prad(x)		(x/1391400.0)

double planet[]={
	80,80,	pmass(333000.0),pdis(0),		pper(1),		pgrav(333000.0),	prad(1391400.0),0,

	80,80,	pmass(0.0553),	pdis(57900.0),	pper(88.0),		pgrav(0.0553),		prad(4879.0),0,
	80,80,	pmass(0.815),	pdis(108200.0),	pper(224.7),	pgrav(0.815),		prad(12104.0),0,
	80,80,	pmass(1.0),		pdis(149600.0),	pper(365.2),	pgrav(1.0),			prad(12756.0),0,
	80,80,	pmass(0.1075),	pdis(227900.0),	pper(687.0),	pgrav(0.1075),		prad(6792.0),0,

	80,80,	pmass(317.8),	pdis(778600.0),	pper(4331.0),	pgrav(317.8),		prad(142984.0),0,
	80,80,	pmass(95.2),	pdis(1433500.0),pper(10747.0),	pgrav(95.2),		prad(120536.0),0,
	80,80,	pmass(14.6),	pdis(2872500.0),pper(30589.0),	pgrav(14.6),		prad(51118.0),0,
	80,80,	pmass(17.2),	pdis(4495100.0),pper(59800.0),	pgrav(17.2),		prad(49528.0),0
};
