// 2013013017 윤신웅
// 데이타통신 과제 2 - 1) CRC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 1000

// CRC 함수
void CRC(char*, char*);

// remainder
char fcs[MAX];

void main() {

	// 출력 str
	char str1[] = "1: Dataword to codeword";
	char str2[] = "2: Codeword to dataword";
	char str3[] = "3: Exit";

	// 입력값
	int input;
	char dataword[MAX],dataword2[MAX], divisor[MAX], codeword[MAX];
	int remainder[MAX];
	int size,cnt=0;
	unsigned long dw, dv, dw2, cw, rm;

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
		// dataword -> codeword
		case 1:
			//입력받기
			printf("Dataword : ");
			scanf("%s", dataword);

			printf("Divisor	 : ");
			scanf("%s", divisor);

			// Dataword2 값 추가
			strcpy(dataword2, dataword);
			for (int i = 0 ; i < strlen(divisor)-1; i++) {
				strcat(dataword2, "0");
			}

			// 부호화 -> remainder에 저장
			CRC(dataword2, divisor);

			// Remainder 출력
			printf("Remainder: ");

			// 0은 출력할필요 x
			cnt = 0;
			while(fcs[cnt] == '0') {
				cnt++;
			}
			for (int i = cnt; i < strlen(fcs); i++)
				printf("%c", fcs[i]);
			printf("\n");
			
			// FCS 출력
			printf("FCS      : ");
			printf("%s\n\n", fcs);

			// Codeword 출력
			printf("Codeword : %s",dataword);
			printf("%s\n", fcs);

			break;

		// codeword -> dataword
		case 2:
			//입력받기
			printf("Codeword : ");
			scanf("%s", codeword);

			printf("Divisor	 : ");
			scanf("%s", divisor);

			// 복호화 -> remainder에 저장
			CRC(codeword, divisor);

			// Remainder 출력
			printf("Remainder: ");

			// 0은 출력할필요 x
			cnt = 0;
			while (fcs[cnt] == '0') {
				cnt++;
			}
			for (int i = cnt; i < strlen(fcs); i++)
				printf("%c", fcs[i]);
			printf("\n");

			// FCS 출력
			printf("FCS      : ");
			printf("%s\n\n", fcs);

			// 유효성 체크
			while (fcs[cnt] == '0') {
				cnt++;
			}

			// 유효출력
			if (cnt >= strlen(fcs)) {
				printf("유효함!\n");
				printf("Dataword : ");
				for (int i = 0; i < strlen(codeword) - strlen(divisor)+1; i++)
					printf("%c", codeword[i]);
				printf("\n");
			}
			// 무효출력
			else {
				printf("무효함!\n");
			}

			break;

		// exit
		case 3:
			return;
	}
}

// CRC
void CRC(char * word, char * div) {

	int i,idx=0, wordlen = strlen(word), divlen=strlen(div);
	int buf[MAX], buf2[MAX];

	// 초기값 가져오기
	for (int i = 0; i < strlen(div)-1; i++) {
		if (word[i] == '0')
			buf[i] = 0;
		else
			buf[i] = 1;
	}

	// 나눗셈 반복은 길이차만큼
	while (idx < ((wordlen - divlen)+1)) {
	
		//  끝값 하나 추가
		if (word[idx + divlen - 1] == '0')
			buf[divlen - 1] = 0;
		else
			buf[divlen - 1] = 1;

		// 첫글자가 0 
		if (buf[0] == 0) {
			
			// xor 연산하면서 값 추가
			for (i = 1; i < divlen; i++) {
				buf2[i-1] = buf[i] ^ 0;
			}

			// buf2 -> buf로 값 옮기기
			for (i = 0; i < divlen -1; i++)
				buf[i] = buf2[i];

			// 다음 idx 증가
			idx++;
		}

		// 첫글자가 1
		else if (buf[0] == 1) {
			
			// xor 연산하면서 값 추가
			for (i = 1; i < divlen; i++) {
				buf2[i-1] = buf[i] ^ (div[i]-'0');
			}

			// buf2 -> buf로 값 옮기기
			for (i = 0; i < divlen-1; i++)
				buf[i] = buf2[i];

			// 다음 idx 증가
			idx++;
		}
	}

	// 현재 buf에 최종 remainder 값이 들어가있음
	for (i = 0; i < divlen - 1; i++) {
		fcs[i] = buf[i] + '0';
	}

}