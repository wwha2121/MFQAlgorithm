#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
# define MAX_SIZE 9
//# define SWAP(x, y, temp) ( (temp)=(x), (x)=(y), (y)=(temp) )
//https://gmlwjd9405.github.io/2018/05/10/algorithm-quick-sort.html


#define MAX_QUEUE_SIZE 10
#define MAX_STRING 100
typedef struct Process Process ;
typedef struct{
    int front;
    int rear;
    char name;
    int queuePriority;
    int queueAge;
    Process * process[100];

} Queue;

typedef struct Process {
    int processPriority;
//    int processAge;
    int cpuUsage;
    char *processName;
} Process;

void processSwap(Queue *queue,int low,int high){

    //바꾸기 queue 포인터
    Process *temp = queue->process[low];
    queue->process[low]= queue->process[high];
    queue->process[high] = temp;




}


int partition(Queue *queue, int left, int right){
    int pivot;
    int low, high;



    low = left;
    high = right + 1;

            ;
    pivot = queue->process[left]->cpuUsage;
//    pivot = list[left]; // 정렬할 리스트의 가장 왼쪽 데이터를 피벗으로 선택(임의의 값을 피벗으로 선택)

    /* low와 high가 교차할 때까지 반복(low<high) */
    do{
        /* list[low]가 피벗보다 작으면 계속 low를 증가 */
        do {
            low++; // low는 left+1 에서 시작
        } while (low<=right && queue->process[low]->cpuUsage<pivot);

        /* list[high]가 피벗보다 크면 계속 high를 감소 */
        do {
            high--; //high는 right 에서 시작
        } while (high>=left &&  queue->process[high]->cpuUsage>pivot);

        // 만약 low와 high가 교차하지 않았으면 list[low]를 list[high] 교환
        if(low<high){
//            processSwap(list[low], list[high], temp);
            processSwap(queue,low,high
            );
        }
    } while (low<high);

    // low와 high가 교차했으면 반복문을 빠져나와 list[left]와 list[high]를 교환
    processSwap(queue,left,high);


    // 피벗의 위치인 high를 반환
    return high;
}

// 퀵 정렬
void quick_sort(Queue *queue, int left, int right){

    /* 정렬할 범위가 2개 이상의 데이터이면(리스트의 크기가 0이나 1이 아니면) */
    if(left<right){
        // partition 함수를 호출하여 피벗을 기준으로 리스트를 비균등 분할 -분할(Divide)
        int q = partition(queue, left, right); // q: 피벗의 위치

        // 피벗은 제외한 2개의 부분 리스트를 대상으로 순환 호출
        quick_sort(queue, left, q-1); // (left ~ 피벗 바로 앞) 앞쪽 부분 리스트 정렬 -정복(Conquer)
        quick_sort(queue, q+1, right); // (피벗 바로 뒤 ~ right) 뒤쪽 부분 리스트 정렬 -정복(Conquer)
    }

}
// https://gmlwjd9405.github.io/2018/05/10/algorithm-quick-sort.html







int queue_size(Queue *q){
    return q->rear-q->front;
}

void init_queue(Queue *q){
    q->front=q->rear=0;
}

void error(char *message){
    fprintf(stderr,"%s\n",message);
    exit(1);
}

int is_full(Queue *q){
    return q->rear==MAX_QUEUE_SIZE-1;
}

bool is_empty(Queue *q){
    return q->rear==q->front; // 공백상태
}

void enqueue(Queue *q,Process *process){
    if(is_full(q)){
        error("OVERFLOW");
        return;
    }
    q->process[q->rear++]=process;  //rear값을 증가시킨 후 반환
}



Process  *dequeue(Queue *q){
    if(is_empty(q)){
        error("UNDERFLOW");
    }

    return q->process[q->front++];
    //front값을 증가시킨 후 반환
}

Process *peek(Queue *q){
    if(is_empty(q)){
        error("UNDERFLOW");
    }
    int index=q->front+1; // front값을 변화시키지 않기 위해 별도 변수 선언
    return q->process[index];
}

//typedef struct Queue {

//} Queue;

int main(){
    int timeSlice = 5;
    int min = 0;
    int minIndex = 1000000;
    Queue *queue1 = malloc(sizeof(Queue));
    Queue *queue2 = malloc(sizeof(Queue));
    Queue *queue3 = malloc(sizeof(Queue));

    init_queue(queue1);
    init_queue(queue2);
    init_queue(queue3);

    queue1->queueAge = 0 ;
    queue2->queueAge = 0 ;
    queue3->queueAge = 0 ;


    Process *mailProcess1 = malloc(sizeof(Process));
    Process *gameProcess2 = malloc(sizeof(Process));
    Process *pdfViewerProcess3 = malloc(sizeof(Process));
    Process *codingProcess4 = malloc(sizeof(Process));
    Process *osGraphicProcess5 = malloc(sizeof(Process));
    Process *fileProcess6 = malloc(sizeof(Process));
    Process *backupProcess7 = malloc(sizeof(Process));

    mailProcess1->processName = "mailP1";
    gameProcess2->processName = "gameP2";
    pdfViewerProcess3 ->processName = "pdfP3";
    codingProcess4 ->processName = "codingP4";
    osGraphicProcess5 ->processName = "osP5";
    fileProcess6 ->processName = "fileP6";
    backupProcess7 ->processName = "backupP7";

    mailProcess1->cpuUsage = 7;
    gameProcess2->cpuUsage = 20;
    pdfViewerProcess3 ->cpuUsage = 11;
    codingProcess4->cpuUsage = 4;
    osGraphicProcess5-> cpuUsage = 40;
    fileProcess6->cpuUsage =23;
    backupProcess7 ->cpuUsage  = 5;

    mailProcess1->processPriority = 1;
    gameProcess2->processPriority = 1;
    pdfViewerProcess3->processPriority = 1;
    codingProcess4->processPriority = 2;
    osGraphicProcess5->processPriority = 2;
    fileProcess6->processPriority = 3;
    backupProcess7->processPriority = 3;




    enqueue(queue1,mailProcess1);
    enqueue(queue1,gameProcess2);
    enqueue(queue1, pdfViewerProcess3);
    enqueue(queue2, codingProcess4);
    enqueue(queue2, osGraphicProcess5);
    enqueue(queue3, fileProcess6);
    enqueue(queue3,backupProcess7);

    while(queue1->front != queue1->rear || queue2->front != queue2->rear  || queue3->front != queue3->rear  ){
        quick_sort(queue1, queue1->front,queue1->rear-1);


        if (queue1->front != queue1->rear ){
            for(int i = queue1->front; i <queue1->rear;i++){


                queue1->process[i]->cpuUsage-=timeSlice;

                printf("프로세스 %s가 사용되었습니다\n",queue1->process[i]->processName);
                printf("프로세스의 cpu할당량%d\n",queue1->process[i]->cpuUsage);

                if(queue1->process[i]->cpuUsage<= 0  ){

                    printf("%s 너 끝이야 \n",queue1->process[i]->processName);
                    dequeue(queue1);

                }
            }
        }


        if( queue2 != NULL &&queue2->queueAge >5   ){
            for (int i = queue2->front ; i < queue2->rear; ++i) {
                enqueue(queue1,dequeue(queue2));
            }
            free(queue2);
            queue2 = NULL;
        }
        else if( queue2 != NULL &&queue2->queueAge <=5 ){
            queue2->queueAge += 1;
        }


        if( queue3 != NULL &&queue3->queueAge >10  ){
            for (int i = queue3->front ; i < queue3->rear; ++i) {
                enqueue(queue1,dequeue(queue3));
            }
            free(queue3);
            queue3 = NULL;
        }
        else if( queue3 != NULL &&queue3->queueAge <=10 ) {
            queue3->queueAge += 1;
        }


    }
    printf("끝났다!")






     //그게 아니라면 노화 ㄱㄱ

     // 를 계속 반복 ㄱㄱ 언제까지? 큐1,큐2,큐3의 리스트숫자가 0이 될떄까지

//    while(){
//        minIndex = 1000000;
//
//        int i;
//        int n = MAX_SIZE;
//        int list[n] = {5, 3, 8, 4, 9, 1, 6, 2, 7};
//
//        // 퀵 정렬 수행(left: 배열의 시작 = 0, right: 배열의 끝 = 8)
//        quick_sort(list, 0, n-1);
//
//
//        https://gmlwjd9405.github.io/2018/05/10/algorithm-quick-sort.html
//
//
//        for(int i = queue1->rear ; i < queue1->front; i++){
//            if(min < queue1->process[i]){
//                minIndex = i;
//                min = queue1->process[i];
//            }
//        }
//        queue1->process[minIndex]->cpuUsage -= timeSlice;
//        if(queue1->process[minIndex]->cpuUsage<0){
//            dequeue(queue1);
//        }
//
//        for(int i = queue2->rear ; i < queue2->front; i++){
//            queue2->process[i]->processAge+=1
//
//            if(queue2->process[i]->processAge> 20){
//
//            }
//        }
//        for(int i = queue3->rear ; i < queue3->front; i++){
//            queue3->process[i]->processAge+=1
//
//            if(queue3->process[i]->processAge> 30){
//
//            }
//        }
//
//        queue1->process[minIndex]->processPriority = 3;
//        for(int i = 0 ; i < queue_size(queue1) ; i++ ){
//            enqueue(queue2,queue2->rear) // aging1
//            dequeue(queue1)               //aging2
//            enqueue(queue3,queue2->rear) // aging1
//            dequeue(queue2)               //aging2
//        }
//    }


;


    return 0;



}

//프로그램의 교훈 stm을 아낄려면 ltm을 많이 챙기자
//우선순위를 어케세우지 1에 몰리면 거기서 다 뽑으면도지 어떻든 늙으면 우선순위를 줘야하지지지지지~

//큐1에서만 보면 일단 타임슬라이스배정된4만큼 다 쓰고 이제 순서를 제일 작은 놈 순서대로 또 다시 반복~
// 큐 순위대로1,2,3 하고 1끝나야 2끝
//근데 2에있던게 너무 에이징이 들어들면 1에 넣는다..!

//struct readyQueue{
//
//}
//// readyQueue : use cpu
//
//struct waitQueue{
//
//}
//waiting Queue : use I/O



//다단계 큐

