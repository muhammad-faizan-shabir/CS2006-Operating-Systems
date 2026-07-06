status = 0; // 0 for empty, 1 for comedy, 2 for drama

mutex = 1;
comedyMutex = 1;
dramaMutex = 1;

comedyCount = 0;
dramaCount = 0;

comedy_fan_wants_to_enter();
// enter the section
comedy_fan_leaves();

drama_enthusiast_wants_to_enter();
// enter the section
drama_enthusiast_leaves();

// comedy enter
void comedy_fan_wants_to_enter()
{
	wait(mutex); // mutex to handle critical section i.e. comedyCount and dramaCount
	comedyCount++;
	if (comedyCount == 1)  // the first comdey fan to enter locks the comdey semaphore
	{
		wait(comedyMutex);
	}
	if (status==0 or status==1) // this signifies that either the section is empty or the section has comedy fans
	{
		status = 1; // set status to 1 while entering
		signal(mutex); // unlock mutex and enter into the section
	}
	else
	{
		signal(mutex); // unlock mutex
		wait(dramaMutex); // wait for drama fans to leave
		wait(mutex);
		status = 1; // set status to 1 while entering
		signal(mutex);
	}
}

// drama enter
void drama_enthusiast_wants_to_enter()
{
	wait(mutex); // mutex to handle critical section i.e. comedyCount and dramaCount
	dramaCount++;
	if (dramaCount == 1) // the first drama fan to enter locks the drama semaphore
	{
		wait(dramaMutex);
	}
	if (status==0 or status==2) // this signifies that either the section is empty or the section has drama fans
	{
		status = 2; // set status to 2 while entering
		signal(mutex); // unlock mutex and enter into the section
	}
	else
	{
		signal(mutex); // unlock mutex
		wait(comedyMutex); // wait for comedy fans to leave
		wait(mutex);
		status = 2;        // set status to 2 while entering
		signal(mutex);
	}
}



// comdey leave
void comedy_fan_leaves()
{
	wait(mutex); // mutex to handle critical section i.e. comedyCount and dramaCount
	comedyCount--;
	if (comedyCount == 0) // if the last comedy fan leaves then unlock comdeyMutex so that drama fans' wait gets over
	{
		status = 0; // the section is empty now
		signal(comedyMutex);
	}
	signal(mutex);

}

// drama leave 
void drama_enthusiast_leaves()
{
	wait(mutex); // mutex to handle critical section i.e. comedyCount and dramaCount
	dramaCount--;
	if (dramaCount == 0) // if the last drama fan leaves then unlock dramaMutex so that comedy fans' wait gets over
	{
		status = 0; // the section is empty now
		signal(dramaMutex);
	}
	signal(mutex);
}





