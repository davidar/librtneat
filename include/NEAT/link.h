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

// Modified by David Roberts 2010

#ifndef _NEAT_LINK_H_
#define _NEAT_LINK_H_

#include "neat.h"
#include "trait.h"
#include "nnode.h"

namespace NEAT {

	class NNode;

	// ----------------------------------------------------------------------- 
	// A LINK is a connection from one node to another with an associated weight 
	// It can be marked as recurrent 
	// Its parameters are made public for efficiency 
	class Link {
	public: 
		double weight; // Weight of connection
		NNode *in_node; // NNode inputting into the link
		NNode *out_node; // NNode that the link affects
		bool is_recurrent;
		bool time_delay;

		Trait *linktrait; // Points to a trait of parameters for genetic creation

		int trait_id;  // identify the trait derived by this link

		// ************ LEARNING PARAMETERS *********** 
		// These are link-related parameters that change during Hebbian type learning

		double added_weight;  // The amount of weight adjustment 
		double params[NEAT::num_trait_params];

		Link(double w,NNode *inode,NNode *onode,bool recur);

		// Including a trait pointer in the Link creation
		Link(Trait *lt,double w,NNode *inode,NNode *onode,bool recur);

		// For when you don't know the connections yet
		Link(double w);

		// Copy Constructor
		Link(const Link& link);

		// Derive a trait into link params
		void derive_trait(Trait *curtrait);

	};

} // namespace NEAT

#endif
