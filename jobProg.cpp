// This file will build all my functions from the .h file and 
// build the constuctors and destructors of the linear linked lists



#include "job.h" // brings in .h file

// initiates list build and sets location and job heads to NULL
list::list(){


  head = NULL;
//  fileIn(head);// cannot get file to write in correctly
  //head2 = NULL;

}
// outputs data to file and destructs
list::~list(){
  
  int temp = 0;
  if(head)
  {
//    cout << "test";
  temp = fileOut(head);
  }
  if(temp == 1)
  {
    deleteNodes();
  }


}
int list::deleteNodes(){

  local * current = head;

  while(head)
  {

    job * curr = head->head2;
    current = head->next;
    while(curr)
    {
      job * temp = curr;
      temp = curr->next;
      delete curr;
      curr = temp;
    }

    delete head;
    head = current;
  }


}
// outputs data to jobList.txt

int list::fileOut(local * head){

  ofstream file_out;
  file_out.open("jobList.txt",ios::app);

  if(!head) return -1;


  while(head)
  
  {
    file_out << '/' << head->location << ':' << '\n';

    job * curr = head->head2;

    while(curr)
    {
      file_out << '&' << curr->compName << '&' << curr->qualifications << '&'
               << curr->qualifications << '&' << curr->jobSpec << '&'
               << curr->degree << '&' << curr->payRate << '&'
               << curr->rating << '&' << curr->review << '&' << ':' << '\n';

      curr = curr->next;
    }

    head = head->next;

  }
  file_out.clear();
  file_out.close();
  return 1;
}
/*int list::addLoc(local * to_addLoc)
{
  if(!to_addLoc) return -1;

  to_addLoc->next = head;
  head = to_addLoc;

  return 1;

}
int list::addJob(job * to_addJob)
{
  if(!to_addJob) return -1;

  if(!head) return -1;
  
  to_addJob->next = head->head2;
  head->head2 = to_addJob;

  return 1;


}*/

// checks for info in job.txt
int list::fileIn(local * & head){
  ifstream file_in;
  file_in.open("jobList.txt");

//  local * curr = head;

  char buff[1000];
  char buff2[1000];
  int count = 1;
  int count2 = 0;
  if(file_in)
  {
    if(file_in.peek() != '/') return -1;

    file_in.get(buff,1000,'\n');
    file_in.ignore(1000,'\n');
    local * currLocation = new local;
    job * currJob = NULL;
    head = currLocation;;
    
    while(buff[count] != ':') // copies line up to delimiter
    {
      buff2[count2] = buff[count];
      ++count;
      ++count2;
    }
    buff2[count2] = '\0';
    currLocation->location = new char[strlen(buff2)+1];
    strcpy(currLocation->location,buff2);


    

    currLocation->next = NULL;


    while(file_in && !file_in.eof())
    {

      int section = 0;
      int count2 = 0;
      count = 1;
      
      file_in.get(buff,1000,'\n');
      file_in.ignore(1000,'\n');
      if(buff[0] == '&') // catches jobs
      {

        currJob = new job;
        head->head2 = currJob;


        {
          if(buff[count] != '&') // catches first job section
          {
            buff2[count2] = buff[count]; // copies line up to delimiter
            ++count2;
 
          }
          else
          {

        
            buff2[count2] = '\0';// adds null to end of string
            if(section == 0) // adding name for 1st section
            {

              currJob->compName = new char[strlen(buff2)+1];
              strcpy(currJob->compName,buff2);
            }
            if(section == 1)
            {

              currJob->description = new char[strlen(buff2)+1];
              strcpy(currJob->description,buff2);
            }
            if(section == 2)
            {
              currJob->qualifications = new char[strlen(buff2)+1];
              strcpy(currJob->qualifications,buff2);

            }
            if(section == 3)
            {
              currJob->jobSpec = new char[strlen(buff2)+1];
              strcpy(currJob->jobSpec,buff2);

            }
            if(section == 4);
            {
              currJob->degree = new char[strlen(buff2)+1];
              strcpy(currJob->degree,buff2);

            }
            if(section == 5)
            {
             
              currJob->payRate = strtof(buff2,NULL);
              
            }
            if(section == 6)
            {
              currJob->rating = strtol(buff2,NULL,10);

            }
            if(section == 7)
            {
              currJob->review = new char[strlen(buff2)+1];
              strcpy(currJob->review,buff2);
            }
            ++section;
            count2 = 0;
          }
          ++count;
        }
      }
      if(buff[0] == '/') // catches locations
      {
        count = 1;
        count2 = 0;

        currLocation->next = new local;
        currLocation = currLocation->next;
        while(buff[count] != ':')
        {
          buff2[count2] = buff[count];
          ++count;
          ++count2;
        }
        buff2[count-1] = '\0'; // adds null to end of char array
        currLocation->location = new char[strlen(buff2)+1];
        strcpy(currLocation->location,buff2);

        currLocation->next = NULL;

      }


    }
    file_in.clear();
    file_in.close();
  }
  
}
// wrapper function for keeping data private
int list::editJobs(){

  findJob(head);

}
// this will traverse the location LLL to send information to the review edit
int list::findJob(local * head){

  if(!head) return -1;

  char * temp = new char[20];  

  cout << "Please enter the Job whose review you would like to change: ";
  cin.get(temp,20);
  cin.ignore(100,'\n');


    int jobCatch = 0;
    
  while(jobCatch != 1)
  {

    jobCatch = editJobs_Private(head,temp);

    if(jobCatch == -1)
    {
      cout << "No matches found please try again. " << endl;
      return -1;

    } 
    else if(jobCatch != 1)
    {
      head = head->next;
    }
    else if(jobCatch == 1)
    {
      cout << "Edited Sucessfully!!! \n";
      return 1;
    }
  }
  delete [] temp;
  return 1;



}
// this will send in location head to search through each job individually
// if not match returns -1 and goes back to find job if found will change review
int list::editJobs_Private(local * & head, char * temp){

  if(!head) return -1;

  job * curr = head->head2;


  while(curr)
  {

    if(strcmp(temp,curr->compName) == 0)
      {
        cout << "Found a match of " << temp << " and " << curr->compName << endl;

        cout << "Please edit the review: ";

        char * temp = new char[100];
        cin.get(temp,100);
        cin.ignore(100,'\n');
        curr->review = new char[strlen(temp) + 1];
        strcpy(curr->review,temp);
        cout << endl;


        return 1;
      }
    else if(strcmp(temp,curr->compName) != 0)
    {
      curr = curr->next;
    }
  }
  return 0;

}
// this will search for a certain location that user needs
int list::displayLocationJobsPriv(local * head){

  if(!head) return -1;

  job * curr = head->head2; // creates pointer to head2 point for job list

  char * temp = new char[20];
  cout << "Please enter the Location you are looking for to display jobs: ";
  cin.get(temp,20);
  cin.ignore(100,'\n');
  if(strcmp(temp,head->location) == 0)
  {
    
    cout << "Jobs in " << head->location << endl; 

    while(curr)
    {
      displayPrivateJobs(curr);
      curr = curr->next;
    }

    return 1;

  }
  
  while(head->next)
  {
      if(strcmp(temp,head->location) != 0) 
      {
        head = head->next;
        curr = head->head2;

      }

  }
  if(strcmp(temp,head->location) != 0)
  {
    cout << "NO MATCHES" << endl;
    return -1;
  }
  
  cout << "Jobs in " << head->location << endl; 

  while(curr)
    {
      displayPrivateJobs(curr);
      curr = curr->next;
    }


  return 1;


}
// wrapper function to access certain jobs by location
int list::displayLocationJobs(){

  displayLocationJobsPriv(head);

}
int list::buildPrivate_Jobs(job * & head2){

  cout << "Please enter the name of the Company: ";
  char * temp = new char[20];
  cin.get(temp,20);
  cin.ignore(100,'\n');
  head2->compName = new char[strlen(temp) + 1];
  strcpy(head2->compName,temp);
  cout << endl;

  cout << "Please enter the job description: ";
  char * temp2 = new char[100];
  cin.get(temp2,100);
  cin.ignore(100,'\n');
  head2->description = new char[strlen(temp2) + 1];
  strcpy(head2->description,temp2);
  cout << endl;

  cout << "Please enter qualifications required(e.g. C++, Java): ";
  cin.get(temp2,100);
  cin.ignore(100,'\n');
  head2->qualifications = new char[strlen(temp2) + 1];
  strcpy(head2->qualifications,temp2);
  cout << endl;

  cout << "Please enter job type(e.g. Internship, Permanent): ";
  cin.get(temp,20);
  cin.ignore(100,'\n');
  head2->jobSpec = new char[strlen(temp) + 1];
  strcpy(head2->jobSpec,temp);
  cout << endl;

  cout << "Please enter degree required(e.g. Associate, Bachelor): ";
  cin.get(temp,20);
  cin.ignore(100,'\n');
  head2->degree = new char[strlen(temp)+1];
  strcpy(head2->degree,temp);
  cout << endl;

  cout << "Please enter the monthly salary: ";
  cin >> head2->payRate;
  cin.ignore(100,'\n');
  cout << endl;

  cout << "Please enter a rating 1 for worst 5 for best: ";
  cin >> head2->rating;
  cin.ignore(100,'\n');
  cout << endl;

  cout << "Please write a small review for the company: ";
  cin.get(temp2,100);
  cin.ignore(100,'\n');
  head2->review = new char[strlen(temp2)+1];
  strcpy(head2->review,temp2);
  cout << endl; 

  head2->next = NULL;

  delete [] temp;
  delete [] temp2;
}
// builds the job node 
int list::buildJobNode(local * headLoc){

  if(!headLoc->head2)// changed head to headLoc was mixing up pointers
  {
    headLoc->head2 = new job;
    buildPrivate_Jobs(headLoc->head2);
    cout << endl;
    return 1;
  }

  job * current = headLoc->head2;

  while(current->next)
  {
    current = current->next;
  }
  current->next = new job;
  current = current->next;
  buildPrivate_Jobs(current);
  current->next = NULL;

  cout << endl << endl;


}
// wrapper function to keep data private
int list::display(){

  int temp = 0;

  temp = displayPrivate(head);
  if(temp == -1) return -1;

  return 0;
}
// runs display
int list::displayPrivate(local * head){

  if(!head) return -1;

  cout << "LOCATION:" << endl;
  cout << head->location << endl << endl;
  job * curr = head->head2;

  cout << "JOBS:" << endl;
  while(curr)
  {
    displayPrivateJobs(curr);
    curr = curr->next;
  }
  displayPrivate(head->next);
  cout << endl;

  return 1;


}
int list::displayPrivateJobs(job * headJob){
  if(!headJob) return -1;

  cout << "Company Name: " << endl;
  cout << headJob->compName << endl;
  cout << "Description: " << endl;
  cout << headJob->description << endl;
  cout << "Qualifications: " << endl;
  cout << headJob->qualifications << endl;
  cout << "Job Type: " << endl;
  cout << headJob->jobSpec << endl;
  cout << "Degree Required: " << endl;
  cout << headJob->degree << endl;
  cout << "Monthly Salary: " << endl;
  cout << "$ " << headJob->payRate << endl;
  cout << "Company Rating(1-5): " << endl;
  cout << headJob->rating << endl;
  cout << "Company Review: " << endl;
  cout << headJob->review << endl << endl << endl;

  return 1;

}
// yes or no 
bool list::yesNo(){

  bool temp = true;
  char noYes = ' ';

  cin.get(noYes);
  cin.ignore(100, '\n');

  if(toupper(noYes) == 'Y')
    return true;
  else return false;
}
// Builds the location node privately
int list::buildPrivate_Location(local * & headLoc){


  local * curr = headLoc;
  char reply = 'Y';

    cout << "Please enter the name of the Location: ";
    char * temp = new char[20];
    cin.get(temp, 20);
    cin.ignore(100, '\n');
    headLoc->location = new char[strlen(temp) + 1];
    strcpy(headLoc->location, temp);

    headLoc->next = NULL;


  
  cout << "Now enter jobs: \n";
  while(reply == 'Y')
  {
    buildJobNode(headLoc);
    cout << "Would you like to add another job Y/N: ";
    cin >> reply;
    cin.ignore(100,'\n');
    reply = toupper(reply);
    cout << endl;
  }

  delete [] temp;
  return 1;

}
//go again function for location add
bool list::goAgain(){

  char temp;

  cout << "Would you like to add another location Y/N? ";
  cin.get(temp);
  cin.ignore(100, '\n');

  if(toupper(temp) == 'Y')
    return true;

  else return false;

}
int list::buildLocation(){

  buildLocationNode();

}
// Build location lll
int list::buildLocationNode(){

  if(!head)
  {
    head = new local; // builds new location node if list is currently empty
    buildPrivate_Location(head);
    cout << endl;
    return 0;
  }

  local * current = head;

  while(current->next != NULL)
  {
    current = current->next;

  }
  current->next = new local;
  current = current->next;
  buildPrivate_Location(current);
  current->next = NULL;

  cout << endl;
}
// Intro to program 
void list::intro(){

  cout << "Welcome to the job builder program.  This program will prompt you to enter \n"
       << "locations of the jobs you are looking for.  The program will then prompt you \n"
       << "to enter the jobs and their information (rating, requirements, etc.). When \n"
       << "you are done entering the program will then load this information to a file \n"
       << "for later use." << endl << endl << endl;

}

