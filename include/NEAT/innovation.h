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

#ifndef _NEAT_INNOVATION_H_
#define _NEAT_INNOVATION_H_

namespace NEAT {

	enum innovtype {
		NEWNODE = 0,
		NEWLINK = 1
	};

	// ------------------------------------------------------------
	// This Innovation class serves as a way to record innovations
	//   specifically, so that an innovation in one genome can be 
	//   compared with other innovations in the same epoch, and if they
	//   are the same innovation, they can both be assigned the same
	//   innovation number.
    //
	//  This class can encode innovations that represent a new link
	//  forming, or a new node being added.  In each case, two 
	//  nodes fully specify the innovation and where it must have
	//  occured.  (Between them)                                     
	// ------------------------------------------------------------ 
	class Innovation {
	private:
		enum innovtype {
			NEWNODE = 0,
			NEWLINK = 1
		};

		//typedef int innovtype;
		//const int NEWNODE = 0;
		//const int NEWLINK = 1;

	public:
		innovtype innovation_type;  //Either NEWNODE or NEWLINK

		int node_in_id;     //Two nodes specify where the innovation took place
		int node_out_id;

		double innovation_num1;  //The number assigned to the innovation
		double innovation_num2;  // If this is a new node innovation, then there are 2 innovations (links) added for the new node 

		double new_weight;   //  If a link is added, this is its weight 
		int new_traitnum; // If a link is added, this is its connected trait 

		int newnode_id;  // If a new node was created, this is its node_id 

		double old_innov_num;  // If a new node was created, this is the innovnum of the gene's link it is being stuck inside 

		bool recur_flag;

		//Constructor for the new node case
		Innovation(int nin,int nout,double num1,double num2,int newid,double oldinnov);

		//Constructor for new link case
		Innovation(int nin,int nout,double num1,double w,int t);

		//Constructor for a recur link
		Innovation(int nin,int nout,double num1,double w,int t,bool recur);

	};

} // namespace NEAT

#endif
