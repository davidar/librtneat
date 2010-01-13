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

#ifndef _NEAT_TRAIT_H_
#define _NEAT_TRAIT_H_

#include <fstream>
#include "neat.h"

namespace NEAT {

	// ------------------------------------------------------------------ 
	// TRAIT: A Trait is a group of parameters that can be expressed     
	//        as a group more than one time.  Traits save a genetic      
	//        algorithm from having to search vast parameter landscapes  
	//        on every node.  Instead, each node can simply point to a trait 
	//        and those traits can evolve on their own 
	class Trait {

		// ************ LEARNING PARAMETERS *********** 
		// The following parameters are for use in    
		//   neurons that learn through habituation,
		//   sensitization, or Hebbian-type processes  

	public:
		int trait_id; // Used in file saving and loading
		double params[NEAT::num_trait_params]; // Keep traits in an array

		Trait ();

		Trait(int id,double p1,double p2,double p3,double p4,double p5,double p6,double p7,double p8,double p9);

		// Copy Constructor
		Trait(const Trait& t);

		// Create a trait exactly like another trait
		Trait(Trait *t);

		// Special constructor off a file assume word "trait" has been read in
		Trait(const char *argline);

		// Special Constructor creates a new Trait which is the average of 2 existing traits passed in
		Trait(Trait *t1,Trait *t2);

		// Dump trait to a stream
        void print_to_file(std::ostream &outFile);
	void print_to_file(std::ofstream &outFile);

		// Perturb the trait parameters slightly
		void mutate();

	};

} // namespace NEAT

#endif
