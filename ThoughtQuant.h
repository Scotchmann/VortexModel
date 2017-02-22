#ifndef THOUGHTQUANT_H
#define THOUGHTQUANT_H

struct ThoughtQuant
{

    //
    //      a
    //    /   \
    //   b  _  c
    //
	//	root = (a - b) / (a - c)
	//
	//
	
    double root;
    vector<Pole *> ConsolidatesPoles;

};

#endif // THOUGHTQUANT_H