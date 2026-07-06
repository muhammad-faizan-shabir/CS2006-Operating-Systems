Semaphore enterMutex = 1;
Semaphore comedyMutex = 1;
Semaphore dramaMutex = 1;

int comedyCount = 0;
int dramaCount = 0;

while(1) // comedy process
{
	wait(comedyMutex); // comedy_fan_wants_to_enter
	comedyCount++;
	if(comedyCount==1)
	{
		wait(enterMutex);
	}
	signal(comedyMutex);
	// Enter the section
	wait(comedyMutex); // comedy_fan_leaves
	comedyCount--;
	if(comedyCount==0)
	{
		signal(enterMutex);
	}
	signal(comedyMutex);
}

while(1) // drama process
{
	wait(dramaMutex); // drama_enthusiast_wants_to_enter
	dramaCount++;
	if(dramaCount==1)
	{
		wait(enterMutex);
	}
	signal(dramaMutex);
	// Enter the section
	wait(dramaMutex); // drama_enthusiast_leaves
	dramaCount--;
	if(dramaCount==0)
	{
		signal(enterMutex);
	}
	signal(dramaMutex);
}