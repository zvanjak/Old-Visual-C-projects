#if !defined(_IROKDATA_H)
#define _IROKDATA_H	1

#include <stdio.h>
#include "IOptRok.h"

class FileData : public IORDataSource {
public:
	FileData(char *FileExam, char *FileExamData, char *FileGroup, char *FilePresjek);
	~FileData();
		
	RESULT		ResetIterators();

	RESULT		GetNextExam(char *Name, char *Code);
	RESULT		GetNextExamData(char *Code, int *Sem, int*StudNum, int *Group, char *Desc, int *Smjer);
	RESULT		GetNextGroup(char *Name, int *Code);
	RESULT		GetNextPresjek(int *Code1, int *Code2, int *Num );
	RESULT		GetNextSameDayExams(int *Code1, int *Code2);

private:
	FILE		*fpExamName, *fpExamData, *fpGroup, *fpPresjek;
};

class DBData : public IORDataSource {
public:
	RESULT		ResetIterators();

	RESULT		GetNextExam(char *Name, char *Code);
	RESULT		GetNextExamData(char *Code, int *Sem, int*StudNum, int *Group, char *Desc, int *Smjer);
	RESULT		GetNextGroup(char *Name, int *Code);
	RESULT		GetNextPresjek(int *Code1, int *Code2, int *Num );
	RESULT		GetNextSameDayExams(int *Code1, int *Code2);
};

#endif