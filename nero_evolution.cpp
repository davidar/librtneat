/*
Because NERO source code cannot be released at the time of the rtNEAT release, we are
releasing this core evolution method from NERO so that users can still create their own
NERO-like game based on this core method.

Another useful small method is also included below.

The code is commented in detail to facilitate understanding.
*/

// This method is called periodically (every few ticks) during NERO training mode.
// It is the main real-time evolution loop that calls most of the rtNEAT methods.
// A similar periodic (regularly times) method could be implemented in your own game.
// The methods called within are all included in this rtNEAT package.
void NEROFactory::evolveBrains() {

  // Remove the worst organism
  //NEAT::Organism *deadorg = m_Population->remove_worst_probabilistic(); //Danger: doing this makes it not work like NEAT
  NEAT::Organism *deadorg = m_Population->remove_worst(); //removes organism with worst adjusted fitness

  //First figures out how often to adjust the compatibility threshold in order to keep # species constant
  int num_species_target=4;
  int compat_adjust_frequency = m_BrainList.size()/10;
  if (compat_adjust_frequency < 1)
    compat_adjust_frequency = 1;
  
  Vector<NEAT::Organism*>::iterator curorg;
  NEAT::Species *new_species;
  
  // In a truly real-time simulation, rtNEAT takes into account the "age" of different organisms, that is,
  // the time they have been on the field.  If an organism is too young, then it is not considered eligible to
  // be removed no matter how low its fitness is, because it hasn't had a chance to prove itself.
  // Therefore, we only proceed with a replacement if an organism was indeed removed above.
  if (deadorg) {
    NEAT::Organism *new_org = 0; // Get ready for a baby!
    
    // Estimate all species' fitnesses
    // Because the composition of each species is changing over time and rtNEAT uses the average fitness of species
    // in order to decide what to do next, it is necessary to update those averages on a constant basis.
    for (Vector<NEAT::Species*>::iterator curspec = (m_Population->species).begin(); curspec != (m_Population->species).end(); ++curspec) {
      (*curspec)->estimate_average();
      
      //This prints out some debug info to a console associated with the game
      if( s_ConsoleDebug )
	printf("Species %d   size: %d   elig. size: %d   avg. score: %f", (*curspec)->id, (*curspec)->organisms.size(), samplesize, scoreavg);  
    }
     
    // Reproduce a single new organism to replace the one killed off.
    // The offspring is born by first choosing its appropriate parent species,
    // and then calling reproduce_one for that species.
    new_org = (m_Population->choose_parent_species())->reproduce_one(m_OffspringCount,m_Population,m_Population->species, 0,0);

    //Count the new offspring
    ++m_OffspringCount;
    
    //printf("Compat threshold: %f",NEAT::compat_threshold);
    
    // Every few reproductions, reassign the population to new species based on an updated compatibility threshold.
    // Unlike regular NEAT, it is necessary to periodically reorganize species by force in rtNEAT since simply
    // changing the threshold alone does not cause any organisms to move into different species.
    if (m_OffspringCount % compat_adjust_frequency == 0) {
      
      int num_species = m_Population->species.size();
      double compat_mod=0.1;  //Modify compat thresh to control speciation
      
      // This tinkers with the compatibility threshold in order to help hit the target # of species
      if (num_species < num_species_target)
	NEAT::compat_threshold -= compat_mod;
      else if (num_species > num_species_target)
	NEAT::compat_threshold += compat_mod;
      
      // Don't go too low
      if (NEAT::compat_threshold < 0.3) 
	NEAT::compat_threshold = 0.3;
      
      //Go through entire population, reassigning organisms to new species
      for (curorg = (m_Population->organisms).begin(); curorg != (m_Population->organisms).end(); ++curorg) {
	m_Population->reassign_species(*curorg);
      }

    }
    
    // Iterate through all of the Brains, find the one whose Organism was killed off, and link that Brain
    // to the newly created Organism, effectively doing a "hot swap" of the Organisms in that Brain.  
    // NOTE: In your own game, you will likely not do exactly this final step.  However, it may be informative
    //       as a reference in terms of what might be useful.   The idea is that there are actual objects
    //       that represent "bodies" on the screen, and the Organism that was inside of one of these has
    //       now been killed off.  In NERO, the container that used to hold the Organism is called a
    //       NEROBrain, and the Brain is in a NEROBody.  So what this little piece of hoursekeeping does
    //       is find the NEROBrain that lost its Organism, and replace it with the new baby that was 
    //       just born.  It then removes the body containing that NEROBrain from the field (while keeping
    //       the NERO Brain around for a new body. 
    for (Vector<NEROBrain*>::iterator iter = m_BrainList.begin(); iter != m_BrainList.end(); ++iter) {
      if ((*iter)->m_Organism == deadorg) {
	(*iter)->m_Organism = new_org;
	(*iter)->m_Stats.resetAll();
	for (Vector<NEROBody*>::iterator iter2 = m_BodyList.begin(); iter2 != m_BodyList.end(); ++iter2) {
	  if ((*iter2)->getBrain() == (*iter)) {
	    deleteUnit(*iter2);
	    break;
	  }
	}
	break;
      }
    }
    
  }
  
}


// This is the place in NERO where it decides the m_TimeBetweenEvolutions (i.e. the time that passes between one
// replacement and the next.  The formula for this is provided in our research papers, but it is still informative
// to see how NERO actually decides on the number of ticks between replacements.  Note that this computation
// is considered a part of the rtNEAT algorithm.
void NEROFactory::setUnitTimeLimit(int limit) {
  if (limit > 0) {
    s_UnitTimeLimit = limit;
    NEAT::time_alive_minimum = limit;
    if (m_popExists)
      //This is where the ticks between replacements (m_TimeBetweenEvolutions) is determined
      m_TimeBetweenEvolutions = (double)limit / FRACTION_POPULATION_INELIGIBLE_ALLOWED / (double)(m_Population->organisms.size());
    printf("s_UnitTimeLimit = %i, time_alive_minimum = %i, m_TimeBetweenEvolutions = %i", s_UnitTimeLimit, NEAT::time_alive_minimum, m_TimeBetweenEvolutions);
  }
}
