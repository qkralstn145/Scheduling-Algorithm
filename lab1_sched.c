/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 32143862
*	    Student name : 이희진
*
*   lab1_sched.c :
*       - Lab1 source file.
*       - Must contains scueduler algorithm function'definition.
*
*/

#include "/home/heejin/Scheduling-Algorithm/include/lab1_sched_types.h"

int int_pow(int base, int exp)
{
    int result = 1;
    while (exp)
    {
        if (exp & 1)
           result *= base;
        exp /= 2;
        base *= base;
    }
    return result;
}

void FCFS()
{
    //int arr[M][2] = {{0,0},{0,2},{6,4},{7,4},{8,2},{10,1}};
    int arr[M][2] = {{0,0},{0,3},{2,6},{4,4},{6,5},{8,2}};
    //int arr[M][2] = {{0,0},{0,2},{1,5},{3,1},{7,4},{8,5}};
    //int arr[M][2] = {{0,0},{0,3},{0,6},{0,4},{0,5},{0,2}};
    //int arr[8][2] = {{0,0},{0,7},{2,6},{4,4},{6,5},{8,2},{8,6},{9,1}}; // M을 8로 만들고 실행할 것
    int i,j,k,l;
    int loop = 0; // 전체 서비스 가능한 타임
    int ready = 0; //현재 cpu에 프로세스가 올라와있는지 체크
    int output[M][100] = {0}; // 아웃풋 데이터
    int lastdone = 0; // 맨 마지막 프로세스가 종료된 시점
    int allprdone = 0; // 모든 프로세스의 스케쥴링이 종료되었는가

    for (i = 1; i < M; i++) {
        loop += arr[i][1] + arr[i][0];
        //printf("%d %d\n", arr[i][0], arr[i][1]);
    }
    //printf("%d",loop);

    // 총 걸리는 시간 계산
    for (i = 0; i < loop; i++) {
        ready = 0;
        for (j = 1; j < M; j++) {
            if (i >= arr[j][0] && arr[j][1] >= 1) { // 현재 진행 시간에 프로세스가 도착했는지 판단하고 스케쥴링 할 프로세스의 처리시간이 남았는지 확인
                if (ready == 0) { // 레디에 데이터가 들어갈 수 있는지 판단
                    ready = j; // 레디에 데이터 삽입
                    break;
                }
            }
        }

        if (ready > 0) { // 레디에 처리할 프로세스가 존재한다면
            arr[ready][1]--; // 프로세스의 실행시간을 1 줄이고
            output[ready][i] = 1; // 아웃풋 데이터에 입력
        }
        if (arr[M-1][1] < 1) { // 모든 프로세스의 스케쥴링이 종료되었는지 판정
            lastdone = ++i; // 마지막 프로세스가 종료된 시점에서 총 스케쥴링 시간과 lastdone의 시간이 1 차이가 나기 때문에 ++i을 해 줘야 한다. 
            break; // 모든 프로세스 스케쥴링이 끝났기 때문에 종료
        }
    }

    printf("   ");
    for (l = 0; l < lastdone; l++)  {
            printf("%2d   ",l);
        }
        printf("\n    ");
        
        for (l = 0; l < lastdone; l++)  {
            printf("-----");
        }
        printf("\n");

    for (i = 1; i < M; i++) {
        printf("%c ",i+64);
        for (l = 0; l < lastdone; l++)  {
            if (output[i][l] == 1) {
                printf("  ■  ");
            }
            else
                printf("  □  ");
        }
        printf("\n");
    }
}

void SJF()
{
    //int arr[M][2] = {{0,0},{0,2},{6,4},{7,4},{8,2},{10,1}};
    int arr[M][2] = {{0,0},{0,3},{2,6},{4,4},{6,5},{8,2}};
    //int arr[M][2] = {{0,0},{0,2},{1,5},{3,1},{7,4},{8,5}};
    //int arr[M][2] = {{0,0},{0,3},{0,6},{0,4},{0,5},{0,2}};
    //int arr[8][2] = {{0,0},{0,7},{2,6},{4,4},{6,5},{8,2},{8,6},{9,1}}; // M을 8로 만들고 실행할 것
    int i,j,k,l;
    int loop = 0; // 전체 서비스 가능한 타임
    int ready = 0; //현재 cpu에 프로세스가 올라와있는지 체크
    int output[M][100] = {0}; // 아웃풋 데이터
    int lastdone = 0; // 맨 마지막 프로세스가 종료된 시점
    int allprdone = 0; // 모든 프로세스의 스케쥴링이 종료되었는가

    for (i = 1; i < M; i++) {
        loop += arr[i][1]+arr[i][0];
        //printf("%d %d\n", arr[i][0], arr[i][1]);
    }

    for (i = 0; i < loop; i++) {

        allprdone = 0; // 초기화를 해 주어야 매 루프마다 모든 프로세스의 스케쥴링이 끝났는지 체크 가능
        ready = 0;

        for (j = 1; j < M; j++) {

            if (i >=arr[j][0] && arr[j][1] >= 1) { // 현재 진행 시간에 프로세스가 도착했는지 판단하고 스케쥴링 할 프로세스의 처리시간이 남았는지 확인
                if (ready == 0) { // 레디에 데이터가 들어갈 수 있는지 판단
                    ready = j; // 레디에 데이터 삽입
                }
                else if (arr[j][1] < arr[ready][1]) { // 새로 발견한 프로세스가 더 짧은 실행시간을 가지고 있다면 교체하여 실행
                    ready = j;
                }
            }

            if (arr[j][1] < 1) // 모든 프로세스 스케쥴링이 끝났는지 체크
                allprdone++;
        }

        if (ready > 0) { // 레디에 처리할 프로세스가 존재한다면
            arr[ready][1]--; // 프로세스의 실행시간을 1 줄이고
            output[ready][i] = 1; // 아웃풋 데이터에 입력
        }

        if (allprdone == M-1) { // 스케쥴링이 종료되었다면
            lastdone = i; // lastdone이 현재시간을 기억하고 루프 종료
            break;
        }
    }


    printf("   ");
    for (l = 0; l < lastdone; l++)  {
            printf("%2d   ",l);
        }
        printf("\n    ");
        
        for (l = 0; l < lastdone; l++)  {
            printf("-----");
        }
        printf("\n");

    for (i = 1; i < M; i++) {
        printf("%c ",i+64);
        for (l = 0; l < lastdone; l++)  {
            if (output[i][l] == 1) {
                printf("  ■  ");
            }
            else
                printf("  □  ");
        }
        printf("\n");
    }
}

void RR()
{
    //int arr[M][2] = {{0,0},{0,2},{6,4},{7,4},{8,2},{10,1}};
    int arr[M][2] = {{0,0},{0,3},{2,6},{4,4},{6,5},{8,2}};
    //int arr[M][2] = {{0,0},{0,2},{1,5},{3,1},{7,4},{8,5}};
    //int arr[M][2] = {{0,0},{0,3},{0,6},{0,4},{0,5},{0,2}};
    //int arr[8][2] = {{0,0},{0,7},{2,6},{4,4},{6,5},{8,2},{8,6},{9,1}}; // M을 8로 만들고 실행할 것
    int i,j,l,k;
    int q[M] = {0}; // 배고픔 측정용
    int scpr[M] = {0}; // 프로세스가 타임퀀텀을 다 사용했는지 체크
    int timequantom = 1; // 타임퀀텀
    int loop = 0; // 전체 서비스 가능한 타임
    int ready = 0; //현재 cpu에 프로세스가 올라와있는지 체크
    int output[M][100] = {0}; // 아웃풋 데이터
    int lastdone = 0; // 맨 마지막 프로세스가 종료된 시점
    int allprdone = 0; // 모든 프로세스의 스케쥴링이 종료되었는가

    for (i = 1; i < M; i++) {
        loop += arr[i][1] + arr[i][0];
        //printf("%d %d\n", arr[i][0], arr[i][1]);
    }

    for (i = 0; i < loop; i++) {

        if (scpr[ready] % timequantom == 0 || arr[ready][1] < 1) { // 프로세스가 타임퀀텀 만큼 실행되었거나 서비스시간만큼 실행되어서 더 이상 스케쥴링의 대상이 아니게 되었을 때
            scpr[ready] = 0; // 타임퀀텀을 초기화해줌
            q[ready] = 0; // 스케쥴링이 되어 배고픔이 사라짐
            for (k = 1; k < M; k++) {
                if (i >= arr[k][0] && k != ready) // 현재 진행 시간에 프로세스가 도착했는지 판단하고 k 값이 직전에 스케쥴링되었는지 확인
                    q[k]++; // 스케쥴링이 직전에 되지 않았다면 배고픔을 증가시킴
            }
        }
        
        allprdone = 0; // 초기화를 해 주어야 매 루프마다 모든 프로세스의 스케쥴링이 끝났는지 체크 가능
        ready = 0; // 실행할 프로세스를 고르기 전에 초기화

        for (j = 1; j < M; j++) {
            if (i >=arr[j][0] && arr[j][1] >= 1) { // 현재 진행 시간에 프로세스가 도착했는지 판단하고 스케쥴링 할 프로세스의 처리시간이 남았는지 확인
                if (ready == 0) { // 실행할 프로세스를 아직 고르지 못했다면
                    ready = j; // 프로세스를 고름
                }
                else if (q[ready] < q[j]) { // 프로세스를 이미 골랐음에도 지금 스케쥴링할 다른 프로세스가 존재한다면 배고픔 정도를 비교
                    ready = j; // 더 배고프다면 스케쥴링할 프로세스를 교체
                }
            }

            if (arr[j][1] < 1) // 모든 프로세스 스케쥴링이 끝났는지 체크
                allprdone++;
        }

        if (ready > 0) { // 레디 큐에 처리할 프로세스가 존재한다면
            arr[ready][1]--; // 프로세스의 실행시간을 1 줄이고
            output[ready][i] = 1; // 아웃풋 데이터에 입력
            scpr[ready]++;
        }

        if (allprdone == M-1) { // 스케쥴링이 종료되었다면
            lastdone = i; // lastdone이 현재시간을 기억하고 루프 종료
            break;
        }
    }

    printf("RR 의 현재 Time quantom은 1 입니다. 소스에서 수정이 가능합니다.\n");
    printf("   ");
    for (l = 0; l < lastdone; l++)  {
            printf("%2d   ",l);
        }
        printf("\n    ");
        
        for (l = 0; l < lastdone; l++)  {
            printf("-----");
        }
        printf("\n");

    for (i = 1; i < M; i++) {
        printf("%c ",i+64);
        for (l = 0; l < lastdone; l++)  {
            if (output[i][l] == 1) {
                printf("  ■  ");
            }
            else
                printf("  □  ");
        }
        printf("\n");
    }
}

void MLFQ()
{
    //int arr[M][2] = {{0,0},{0,2},{6,4},{7,4},{8,2},{10,1}};
	int arr[M][2] = {{0,0},{0,3},{2,6},{4,4},{6,5},{8,2}};
    //int arr[M][2] = {{0,0},{0,2},{1,5},{3,1},{7,4},{8,5}};
    //int arr[M][2] = {{0,0},{0,3},{0,6},{0,4},{0,5},{0,2}};
    //int arr[8][2] = {{0,0},{0,7},{2,6},{4,4},{6,5},{8,2},{8,6},{9,1}}; // M을 8로 만들고 실행할 것
    //int arr[M][2] = {{0,0},{0,2},{6,4},{7,4},{8,2},{10,1}};
	int i, j, l, k;
	int loop = 0;  // 전체 시간
	int ready = 0; //다음에 스케쥴링할 데이터
	int q[M] = { 0 }; // 배고픔을 저장
	int pr[M] = { 0 }; // 처리된 회수를 저장
	int output[M][100] = { 0 }; //아웃풋 데이터 저장
	int timequantom = 2; // 타임퀀텀
	int scpr[M] = { 0 }; // 프로세스가 타임퀀텀을 다 사용했는지 체크
	int chktime = 0; // 현재 프로세스가 타임퀀텀이내에서 실행되고있는지
	int emptyq = 0; // 현재 큐에 단 하나의 프로세스만 존재하는지
    int lastdone = 0; // 맨 마지막 프로세스가 종료된 시점
    int allprdone = 0; // 모든 프로세스의 스케쥴링이 종료되었는가

    for (i = 1; i < M; i++) {
        loop += arr[i][1] + arr[i][0];

        //printf("%d %d\n", arr[i][0], arr[i][1]);
    }

	for (i = 0; i < loop; i++) {

		if (chktime == 0) { // cpu에 프로세스가 올라가 있는지 확인합니다.
			for (k = 1; k < M; k++) {
				if (i >= arr[k][0] && k != ready) {// 현재 진행 시간에 프로세스가 도착했는지 판단하고 k 값이 직전에 스케쥴링되었는지 확인
					q[k]++; // 스케쥴링이 직전에 되지 않았다면 배고픔을 증가시킴
					scpr[k] = 0; // 스케쥴링이 이뤄지지 않아서 타임퀀텀 초기화
				}
			}
		}

		if (chktime == 0) // cpu에 선점되었는지 확인
			ready = 0; // 실행할 프로세스를 고르기 전에 초기화
		emptyq = 0; // 현재 스케쥴링의 대상인 프로세스 수
        allprdone = 0; // 초기화를 해 주어야 매 루프마다 모든 프로세스의 스케쥴링이 끝났는지 체크 가능

		for (j = 1; j < M; j++) {
			if (i+1 >= arr[j][0] && arr[j][1] > 0) { emptyq++; } // 현재 스케쥴링의 대상이 될 수 있는 프로세스 조사
            
			if (i == arr[j][0] && arr[j][1] >= 1) { // 새롭게 들어온 프로세스라면
				q[j] = 9999; // 가장 높은 우선순위 할당
				if (ready == 0) { // 현재 스케쥴링할 대상을 정하지 않은 상태라면
					ready = j; // 후보에 넣음
				}
			} // 새로 들어온 프로세스는 가장 우선순위 큐에 들어감 

			if (i >= arr[j][0] && arr[j][1] >= 1) { // 현재 진행 시간에 프로세스가 도착했는지 판단하고 스케쥴링 할 프로세스의 처리시간이 남았는지 확인
				if (ready == 0 && chktime == 0) { // 실행할 프로세스를 아직 고르지 못했고 선점된 프로세스가 없다면
					ready = j; // 프로세스를 고름
				}
				else if (pr[ready] > pr[j] && q[j] != 0) { // 실행될 프로세스가 새로 발견한 프로세스보다 더 낮은 우선순위의 큐에 있는지 확인하고 배고픔을 체크 (배고픔을 체크 안할경우 더 낮은 상태의 큐가 무조건 먼저 돌아감) 
					if (chktime == 0) { // 선점되지 않았다면
						ready = j;
					} // 현재 ready에 들어간 프로세스가 타임퀀텀만큼 충분히 돌았는가 판단
				}
			}

            if (arr[j][1] < 1)  // 모든 프로세스 스케쥴링이 끝났는지 체크
                allprdone++; 
		}

		if (ready > 0) { // 스케쥴링 후보에 오른 프로세스를 스케쥴링함
			arr[ready][1]--; // 프로세스의 실행시간을 1 줄이고
			output[ready][i] = 1; // 아웃풋 데이터에 입력
			scpr[ready]++; // 프로세스가 타임퀀텀 사용
			chktime = 1; // 현재 프로세스가 cpu를 사용 중임
			q[ready] = 0; // 스케쥴링이 되어 배고픔이 사라짐
						 //printf("empty? = %d\n",emptyq);
			//printf("%d time %d runs until %d, %c \n", i,scpr[ready] , (int)int_pow(timequantom, pr[ready]), ready + 64);
			if (scpr[ready] == (int)int_pow(timequantom, pr[ready]) || arr[ready][1] < 1) { // 프로세스가 타임퀀텀만큼 다 돌았으면 우선순위 낮은 큐로 들어감
				scpr[ready] = 0; // 주어진 시간만큼 스케쥴링을 다 했기 때문에 초기화
				chktime = 0; // 프로세스가 cpu에서 내려감
				//printf("%d time %c time over\n", i, ready + 64);

				if (emptyq > 1) // 단 하나의 프로세서만 스케쥴링의 대상이 아니라면
					pr[ready]++; // 프로세스의 우선순위를 낮춤
			}
			//printf("pow is %d\n", (int)int_pow(timequantom,pr[ready]));
		}

        if (allprdone == M-1) { // 스케쥴링이 종료되었다면
            lastdone = i; // lastdone이 현재시간을 기억하고 루프 종료
            break;
        }
	}

    printf("MLFQ 의 현재 Time quantom은 1 입니다. 소스에서 수정이 가능합니다.\n");
	printf("   ");
	for (l = 0; l < lastdone; l++) {
		printf("%2d   ", l);
	}
	printf("\n    ");

	for (l = 0; l < lastdone; l++) {
		printf("-----");
	}
	printf("\n");

	for (i = 1; i < M; i++) {
		printf("%c ", i + 64);
		for (l = 0; l < lastdone; l++) {
			if (output[i][l] == 1) {
				printf("  ■  ");
			}
			else
				printf("  □  ");
		}
		printf("\n");
	}
}

void Lottery()
{
    //int arr[M][2] = {{0,0},{0,2},{6,4},{7,4},{8,2},{10,1}};
    int arr[M][2] = {{0,0},{0,3},{2,6},{4,4},{6,5},{8,2}};
    //int arr[M][2] = {{0,0},{0,2},{1,5},{3,1},{7,4},{8,5}};
    //int arr[M][2] = {{0,0},{0,3},{0,6},{0,4},{0,5},{0,2}};
    //int arr[8][2] = {{0,0},{0,7},{2,6},{4,4},{6,5},{8,2},{8,6},{9,1}}; // M을 8로 만들고 실행할 것
    //int arr[8][2] = {{0,0},{0,7},{0,6},{0,4},{0,5},{0,2},{0,6},{0,1}}; // M을 8로 만들고 실행할 것
    int i,j,k,l;
    int loop = 0; 
    int ready = 0;
    int take_tic[M] = {0,10,40,30,20,50}; // 각 프로세스가 가진 스케쥴링 우선도 티켓 case 1 : 프로세스가 가진 티켓이 사용자가 가진 티켓 미만인 경우
    //int take_tic[M] = {0,500,600,200,100,400,300,200}; // 각 프로세스가 가진 스케쥴링 우선도 티켓 case 2 : 프로세스가 가진 티켓이 사용자가 가진 티켓 미만인 경우
    int sumtake = 0; //전체 티켓의 합
    int scpr[M] = {0}; // 티켓의 구간
    int gacha = -1; //뽑자!
    int output[M][100] = {0};
    int lastdone = 0; // 맨 마지막 프로세스가 종료된 시점
    int allprdone = 0; // 모든 프로세스의 스케쥴링이 종료되었는가

    srand((unsigned int)time(NULL));

    printf("프로세스별 부여된 티켓 현황입니다.\n");
    for (i = 1; i < M; i++) {
        sumtake += take_tic[i];
        printf("%c :%d ",i+64,take_tic[i]);
    }
    printf("\n");
    //printf("%d\n",sumtake);

    for (i = 1; i < M; i++) {
        scpr[i] = scpr[i-1] + ((float)take_tic[i] / sumtake + 0.005) * 100;
        //printf("%d ",scpr[i]);
    }
    scpr[M-1] += 1;
    //printf("\n");
    //printf(" %d",scpr[5]);

    for (i = 1; i < M; i++) {
        loop += arr[i][1] + arr[i][0];
        //printf("%d %d\n", arr[i][0], arr[i][1]);
    }


    for (i = 0; i < loop; i++) {

        allprdone = 0;

        for (j = 1; j < M; j++) {

            if (arr[j][1] < 1) // 모든 프로세스 스케쥴링이 끝났는지 체크
                allprdone++;

            if (gacha == -1) {
                gacha = rand() % scpr[M-1]; // 랜덤 티켓을 생성함
                //printf("%d = 새로뽑았어!\n",gacha);
                // 프로세스 비율 :   7 27 20 13 33
                //                0 7 34 54 67 100(+1)
            }
            if (gacha >= scpr[j-1] && gacha < scpr[j]) { // 티켓이 어느 값 사이에 위치하는지 확인함
                //printf("%d 는 %d와 %d 사이에 존재\n",gacha, scpr[j-1], scpr[j]);
                if (i >= arr[j][0] && arr[j][1] >= 1) // 정한 값이 프로세스가 도착하고 실행할 시간이 남아있다면
                {
                    //printf("그리고 실행가능함\n");
                    ready = j; //다음 실행시킬 프로세스로 정함
                    break;
                }
                if (i < arr[j][0] || arr[j][1] < 1) { // 아무때나 값 교체하는게 아니라 다 돌았는데도 티켓 사이값에 해당하는 프로세스를 못 찾았을 경우엔
                    if (ready == 0) {
                        //printf("근데 실행가능하지는 않아 남은실행 %d\n", arr[j][1]);
                        //printf("그러니까 초기화시켜\n");
                        gacha = -1; // 다시 뽑음
                        i--; //뽑았으니 다시 비교에 들어감
                        break;
                    }
                }
            }
        }

        if (ready > 0) { // 레디에 처리할 프로세스가 존재한다면
            arr[ready][1]--; // 프로세스의 실행시간을 1 줄이고
            output[ready][i] = 1; // 아웃풋 데이터에 입력
            ready = 0;
            //printf("그래서 %d 는 정상처리\n",gacha);
            gacha = -1;
        }

        if (allprdone == M-1) { // 스케쥴링이 종료되었다면
            lastdone = ++i; // 마지막 프로세스가 종료된 시점에서 총 스케쥴링 시간과 lastdone의 시간이 1 차이가 나기 때문에 ++i을 해 줘야 한다. 
            break;
        }
    }

    printf("\n");

    printf("   ");
    for (l = 0; l < lastdone; l++)  {
            printf("%2d   ",l);
        }
        printf("\n    ");
        
        for (l = 0; l < lastdone; l++)  {
            printf("-----");
        }
        printf("\n");

    for (i = 1; i < M; i++) {
        printf("%c ",i+64);
        for (l = 0; l < lastdone; l++)  {
            if (output[i][l] == 1) {
                printf("  ■  ");
            }
            else
                printf("  □  ");
        }
        printf("\n");
    }
}
