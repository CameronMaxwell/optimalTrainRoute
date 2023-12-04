#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


// mutex lock for train seperations
pthread_mutex_t lock;

// 500 passangers total, all at station 0
// 50 passengers want to get to Station 1
// 100 passengers want to get to Station 2
// 250 passengers want to get to Station 3
// 100 passengers want to get to Station 4
int station0 = 500, station1 = 0, station2 = 0, station3 = 0, station4 = 0;

// train 0 and 1 sttart with 0 passengers

int train0 = 0, train1 = 0;





void* routine(void* trainID) {

    while (station0 != -1)
    {
        pthread_mutex_lock(&lock); // station and passenger access locked for current triain in excecution
        //collection from station 0
        if (station0>0)
        {
            printf("\nTrain %d ENTERS Station 0\n    Station 0 has %d passengers to pick up\n    Picking up passengers...\n",trainID,station0);
            int localTemp;
            station0 -= 50; // take 50 passangers
            if (trainID == 0 && station0 > 0) // if its train 0 and there are still passangers left then take more
            {
                
                station0 -= 50;
                train0 = 100;
                localTemp = train0;
                sleep(10);
            } else if (trainID == 1) // train 1 can only take 50
            {
                train1 = 50;
                localTemp =train1;
                sleep(5);
            }else {
                train0 = 50; // if theres only 50 left in station 0 then train 0 takes 50
                localTemp = train0;
                sleep(5);
            } 
            printf("    Train %d is at Station 0 and has %d passengers\n    Station 0 has %d passengers to pick up\nTrain 0 LEAVES Station 0\n",trainID,localTemp,station0);   
        }
        
        // drop off passangers to other stations
        //station 1
        
        if (station1<50)
        {
            printf("\nTrain %d ENTERS Station 1\n    Station 1 has %d passengers to drop off\n    Unloading passengers...\n",trainID,50-station1);
            int localTemp;
            if (trainID == 0)
            {
                train0 -= 50;
                station1 = 50;
                localTemp = train0;
            } else {
                train1 -= 50;
                station1 = 50;
                localTemp = 0;
            }    
            sleep(5);
            printf("    Train %d is at station 1 and has %d passangers\n    Station 1 has %d passengers to drop off\nTrain %d LEAVES station 1\n",trainID,localTemp,50-station1,trainID);

        }
        

        //Passanger Check between stations
        if (trainID == 0)
        {
            if (train0 == 0)
            {
                goto returnTripToStation0;
            }
            
        } else if(trainID == 1){
            if (train1 == 0)
            {
                goto returnTripToStation0;
            }
            
        }
        
        
         //station 2
         if (station2<100)
        {
            printf("\nTrain %d ENTERS Station 2\n    Station 2 has %d passengers to drop off\n    Unloading passengers...\n",trainID,100-station2);
            int localTemp;
            if (trainID==0)
            {
                if (train0 == 100&&(100-station2)>50)
                {
                    train0-= 100;
                    station2 += 100;
                    localTemp = train0;
                    sleep(10);
                } else {
                    train0-=50;
                    station2 +=50;
                    localTemp = train0;
                    sleep(5);
                }
            
            } else {
                train1 -= 50;
                station2 += 50;
                localTemp = 0;
                sleep(5);
            }
            printf("    Train %d is at station 2 and has %d passangers\n    Station 2 has %d passengers to drop off\nTrain %d LEAVES station 2\n",trainID,localTemp,100-station2,trainID);
        }
        
        //Passanger Check between stations
        if (trainID == 0)
        {
            if (train0 == 0)
            {
                goto returnTripToStation0;
            }
            
        } else if(trainID == 1){
            if (train1 == 0)
            {
                goto returnTripToStation0;
            }
            
        }
        
        // station 3
        if (station3<250)
        {
            printf("\nTrain %d ENTERS Station 3\n    Station 3 has %d passengers to drop off\n    Unloading passengers...\n",trainID,250-station3);
            int localTemp;
            if (trainID==0)
            {
                if (train0 == 100 && (250-station3)>50)
                {
                    train0-= 100;
                    station3 += 100;
                    localTemp = 0;
                    sleep(10);
                } else {
                    train0-=50;
                    station3 +=50;
                    localTemp = train0;
                    sleep(5);
                }
            
            } else {
                train1 -= 50;
                station3 += 50;
                localTemp = 0;
                sleep(5);
            }
            printf("    Train %d is at station 3 and has %d passangers\n    Station 3 has %d passengers to drop off\nTrain %d LEAVES station 3\n",trainID,localTemp,250-station3,trainID);
        }
        
        //Passanger Check between stations
        if (trainID == 0)
        {
            if (train0 == 0)
            {
                goto returnTripToStation0;
            }
            
        } else if(trainID == 1) {
            if (train1 == 0)
            {
                goto returnTripToStation0;
            }
            
        }
        
        //station 4
        if (station4<100)
        {
            printf("\nTrain %d ENTERS Station 4\n    Station 4 has %d passengers to drop off\n    Unloading passengers...\n",trainID,100-station4);
            int localTemp;
            if (trainID==0)
            {
                if (train0 == 100 && (100-station4)>50)
                {
                    train0-= 100;
                    station4 += 100;
                    localTemp = 0;
                    sleep(10);
                } else {
                    train0-=50;
                    station4 +=50;
                    localTemp = train0;
                    sleep(5);
                }
            
            } else {
                train1 -= 50;
                station4 += 50;
                localTemp = 0;
                sleep(5);
            }
        printf("    Train %d is at station 4 and has %d passangers\n    Station 4 has %d passengers to drop off\nTrain %d LEAVES station 4\n",trainID,localTemp,100-station4,trainID);
        }


        returnTripToStation0:
        pthread_mutex_unlock(&lock); // the other train may now enter the excecution line
        sleep(2);
        if (station0 == 0&& station4 == 100)
        {
           exit(0);
        }
        
    }
    return NULL;
}
    


int main(int argc, char* argv[]) {
    
    pthread_mutex_init(&lock, NULL); // lock created

    // train ids
    int idTrain0 = 0;
    int idTrain1 = 1;
   

    pthread_t t0,t1; // train 1 and train 0 threads initialized
   
    pthread_create(t0,NULL,routine,idTrain0); // thread 0 created
    pthread_create(t1,NULL,routine,idTrain1); // thread 1 created
   
    pthread_join(t0,NULL); // thread 0 joining the excecution
    pthread_join(t1,NULL); // thread 1 joining the excecution

    pthread_mutex_destroy(&lock); // lock destroyed

    return 0;
}