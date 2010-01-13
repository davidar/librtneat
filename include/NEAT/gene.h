/*
 * Copyright (C) The University of Texas, 2006. All rights reserved.
 * UNIVERSITY EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES CONCERNING THIS
 * SOFTWARE AND DOCUMENTATION, INCLUDING ANY WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR ANY PARTICULAR PURPOSE, NON-INFRINGEMENT
 * AND WARRANTIES OF PERFORMANCE, AND ANY WARRANTY THAT MIGHT OTHERWISE
 * ARISE FROM COURSE OF DEALING OR USAGE OF TRADE. NO WARRANTY IS EITHER
 * EXPRESS OR IMPLIED WITH RESPECT TO THE USE OF THE SOFTWARE OR
 * DOCUMENTATION. Under no circumstances shall University be liable for
 * incidental, special, indirect, direct or consequential damages or loss
 * of profits, interruption of business, or related expenses which may
 * arise from use of Software or Documentation, including but not limited
 * to those resulting from defects in Software and/or Documentation, or
 * loss or inaccuracy of data of any kind.
 */

// Modifications made by David Roberts <d@vidr.cc>, 2010.

#ifndef _NEAT_GENE_H_
#define _NEAT_GENE_H_

#include "neat.h"
#include "trait.h"
#include "link.h"
#include "network.h"

namespace NEAT {

	class Gene {
	public:

		Link *lnk;
		double innovation_num;
		double mutation_num;  //Used to see how much mutation has changed the link
		bool enable;  //When this is off the Gene is disabled
		bool frozen;  //When frozen, the linkweight cannot be mutated

		//Construct a gene with no trait
		Gene(double w,NNode *inode,NNode *onode,bool recur,double innov,double mnum);

		//Construct a gene with a trait
		Gene(Trait *tp,double w,NNode *inode,NNode *onode,bool recur,double innov,double mnum);

		//Construct a gene off of another gene as a duplicate
		Gene(Gene *g,Trait *tp,NNode *inode,NNode *onode);

		//Construct a gene from a file spec given traits and nodes
		Gene(const char *argline, std::vector<Trait*> &traits, std::vector<NNode*> &nodes);

		// Copy Constructor
		Gene(const Gene& gene);

		~Gene();

		//Print gene to a file- called from Genome
        void print_to_file(std::ostream &outFile);
	void print_to_file(std::ofstream &outFile);
	};

} // namespace NEAT


#endif
