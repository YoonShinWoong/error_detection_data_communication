// 2013013017 윤신웅
// 데이타통신 과제 2 - 2) CheckSum

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000

// 16진수 문자열, 정수 변환하기
int hexToInt(char hex);
char intToHex(int data);
void intToBin(int, int, int);
void binToComp(int);
void checksum(int,int);

// data
char send[MAX], recv[MAX];
char bin[MAX][MAX]; // 이진값 반환
char compBin[MAX][MAX]; // 이진값 보수 반환
int B[MAX];				// 이진값 저장
int compB[MAX];			// 이진보수값 저장
char sumBin[MAX];		// SUM bin
char CsumBin[MAX];		// CSUM bin
int checksumInt[4];		// checksumInt

void main() {

	int input;
	int n = 0, i;
	int data;
	int sum = 0, csum = 0;

	// 출력 str
	char str1[] = "1: 송신";
	char str2[] = "2: 수신";
	char str3[] = "3: Exit";

	// 메세지 출력
	char str4[] = "송신 메세지(16진수) 입력:";
	char str5[] = "수신 메세지(16진수) 입력:";
	char str6[] = "<2진수 변환>";

	// 메인 로직
	// 출력 화면
	printf("%s\n%s\n%s\n", str1, str2, str3);
	printf("> ");

	// 버퍼 비우기
	fflush(stdin);

	// 입력 받기
	scanf("%d", &input);

	// 옵션 선택
	switch (input) {
		// 송신
		case 1:
			// 16진수 입력받기
			printf("%s", str4);
			scanf("%s", send);

			// 16진수 -> 정수
			// i는 4마다 체크 (16 비트)
			for (i = 0; i < strlen(send); i += 4) {
				for (int j = i; j < i + 4; j++) {
					data = hexToInt(send[j]);
					intToBin(n, 4 * (j - i), data); // bin 문자열에 값 넣기
				}
				n++; // 다음 word
			}

			// 2진수 변환
			printf("%s\n", str6);
			
			// 덧셈 값 
			for (i = 0; i < strlen(send) / 4; i++) {
				printf("%s\n", bin[i]);
				B[i] = (int)strtol(bin[i], NULL, 2); // 값 변환 후 저장
				sum += B[i]; // 덧셈
			}

			// checkSum 처리
			checksum(sum,i);
			
			// sum 출력
			printf("Sum: %s\n", sumBin);
			
			// checksum 출력
			printf("Checksum: ");
			for (i = 0; i < 4; i++) {
				printf("%c ", intToHex(checksumInt[i]));
			}
			printf("\n");

			// 송신메세지 출력
			printf("송신 측 : ");
			for (i = 0; i < strlen(send); i++) {
				printf("%c", send[i]);
				if (i % 2 == 1)
					printf(" "); //2칸마다 칸 띄우기
			}

			printf("[");
			// checksum 출력
			for (i = 0; i < 4; i++) {
				printf("%c", intToHex(checksumInt[i]));
				if (i == 1)
					printf(" "); //2칸마다 칸 띄우기
			}
			printf("]\n");
			break;

			// 수신
		case 2:
			// 16진수 입력받기
			printf("%s", str5);
			scanf("%s", recv);

			// 16진수 -> 정수
			// i는 4마다 체크 (16 비트)
			for (i = 0; i < strlen(recv); i += 4) {
				for (int j = i; j < i + 4; j++) {
					data = hexToInt(recv[j]);
					intToBin(n, 4 * (j - i), data); // bin 문자열에 값 넣기
				}
				n++; // 다음 word
			}

			// 2진수 변환
			printf("%s\n", str6);

			// 덧셈 값 
			for (i = 0; i < strlen(recv) / 4; i++) {
				printf("%s\n", bin[i]);
				B[i] = (int)strtol(bin[i], NULL, 2); // 값 변환 후 저장
				sum += B[i]; // 덧셈
			}

			// checkSum 처리
			checksum(sum, i);

			// sum 출력
			printf("Sum: %s\n", sumBin);

			// Calculated checksum 출력
			printf("Calculated Checksum: ");
			for (i = 0; i < 4; i++) {
				printf("%c ", intToHex(checksumInt[i]));
			}
			printf("\n");

			// 오류체크
			if (checksumInt[0] == 0 && checksumInt[1] == 0 && checksumInt[2] == 0 && checksumInt[3] == 0) {
				printf("오류 없음\n");
			}
			else
				printf("오류 있음\n");
			
			break;
			
			//exit
		case 3:
			return;
	}

}


// 16진수 문자열 -> 정수 변환하기
int hexToInt(char hex) {

	// 값 반환
	switch (hex) {
		
		// F 
		case 'f':
			return 15;

		// E
		case 'e':
			return 14;

		// D
		case 'd':
			return 13;

		// C
		case 'c':
			return 12;

		// B
		case 'b':
			return 11;

		// A
		case 'a':
			return 10;

		// 0~9
		default:
			return hex - '0';
	}

}

// 정수 -> 16진수 문자열 변환하기
char intToHex(int data) {

	// 값 반환
	switch (data) {

			// F 
		case 15:
			return 'F';

			// E
		case 14:
			return 'E';

			// D
		case 13:
			return 'D';

			// C
		case 12:
			return 'C';

			// B
		case 11:
			return 'B';

			// A
		case 10:
			return 'A';

			// 0~9
		default:
			return data+'0';
	}

}

// 16진수 ->  정수 -> 4bit 이진수 배열에 넣기
void intToBin(int i, int j, int data) {
	// 값 넣기
	for (int cnt = 3; cnt >=0; cnt--) {
		bin[i][j+cnt] = (data % 2 )+ '0';
		data = data / 2;
	}
}

// 보수
void binToComp(int i) {
	for (int j = 0; j < 16; j++) {
		if (bin[i][j] == '0')
			compBin[i][j] = '1';
		else
			compBin[i][j] = '0';
	}
}

// sum을 2진수 문자열로 변환
void checksum(int sum, int n) {

	char binary[MAX];
	char buf[MAX];
	char buf2[MAX];
	char buf3[MAX];
	int data = sum;
	int i = 0;
	int cnt = 0;

	// data가 0 이 아닐동안
	while (data) {
		binary[i++] = data % 2 +'0'; // 문자 처리
		data = data / 2;
	}

	// 문자열뒤집기
	for (int j = 0; j < i; j++) {
		buf[j] = binary[i-1-j];
	}

	// 문자열 (삐져나온 carry 값 내려서 더해주기)
	// buf 2 = 16자리 sum
	for (int j = i - 16; j < i; j++) {
		buf2[cnt++] = buf[j];
	}
	buf2[cnt] = NULL;

	cnt = 0;
	// buf 3 = carry 값
	for (int j = 0; j < i - 16; j++) {
		buf3[cnt++] = buf[j];
	}
	buf3[cnt] = NULL;

	// 값 가져오기
	int data1 = (int)strtol(buf2, NULL, 2);
	int data2 = (int)strtol(buf3, NULL, 2);

	// 더해주기
	int data3 = data1 + data2;

	// data3 -> 2진수 변환
	// data3가 0 이 아닐동안
	i = 0;
	while (data3) {
		binary[i++] = data3 % 2 + '0'; // 문자 처리
		data3 = data3 / 2;
	}

	// 문자열뒤집기
	for (int j = 0; j < i; j++) {
		sumBin[j] = binary[i - 1 - j];
	}

	// 보수 취하기
	for (int j = 0; j < 16; j++) {
		if (sumBin[j] == '0')
			CsumBin[j] = '1';
		else
			CsumBin[j] = '0';
	}

	// 4개씩 문자열 자르기
	int z = 0;
	cnt = 0;
	char csumBin[4][5];
	for (int k = 0; k < 16; k += 4) {
		for (int l = k; l < k + 4; l++) {
			csumBin[cnt][z++] = CsumBin[l];
		}
		cnt++; // 다음값
		csumBin[cnt][4] = NULL; // 문자열만들기
		z = 0; // 초기화
	}
	

	// 값 반환 하나씩
	for (i = 0; i < 4; i++) {
		checksumInt[i] = (int)strtol(csumBin[i], NULL, 2); // 2진값 반환 넘기기
	}
}