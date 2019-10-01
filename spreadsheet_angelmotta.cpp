#include <cstdio>
#include <vector>

using namespace std;

struct formula{
	int row = 0, col = 0;
	//char *form = nullptr;
	char form[100000];
	formula(int _row, int _col, char *_form){
		//printf("This form: %s\n", _form);
		row = _row;
		col = _col;
		//form = _form;
		strcpy(form,_form);
	}

	/*~formula(){
		printf("%s\n","Calling Destructor FORMULA");
	}*/
};

struct spreadhsheet{
	int rows = 0, cols = 0;
	int **arr_spread = nullptr;
	vector<formula> formulas_vec;
	spreadhsheet(int _rows, int _cols){
		rows = _rows;
		cols = _cols;
		arr_spread = new int *[rows];
		//printf("%s\n", "Constructor called");
		for(int i=0; i<rows; ++i){
			arr_spread[i] = new int[cols];
		}
	}

	void input_values(){
		int value = 0;
		//char *str_value = nullptr;
		char str_value[100000];
		size_t n;
		for(int i=0; i<rows; ++i){
			for(int j=0; j<cols; ++j){
				/*if(i == 1 && j == 1){
					printf("fffxread Formula: %s \n",formulas_vec[j-1].form);
				}*/
				//scanf("%d",&value);
				scanf("%99999s", str_value);
				//printf("Ingresaste: %s\n",str_value);
				if(str_value[0] == '='){
					//printf("Guardar formula: %s\n",str_value);
					formula f1(i,j,str_value);
					formulas_vec.push_back(f1);
					printf("read Formula: %s \n",formulas_vec[j].form);
					arr_spread[i][j] = 0;
				}
				else{
					arr_spread[i][j] = atoi(str_value);
				}
				//printf("Ingresaste: %s\n",str_value);
				//arr_spread[i][j] = value;
			}
		}
		//printf("xxxxread Formula: %s \n",formulas_vec[1].form);
	}

	void print_formulas(){
		printf("%s\n", "-- Print Vector of formulas --");
		for(auto f1 : formulas_vec){
			printf("Formula: %s - En Fila: %d - En columna: %d \n", f1.form, f1.row, f1.col);
		}
		/*for(auto it = formulas_vec.begin(); it != formulas_vec.end(); ++it){
			printf("%s\n", (*it).form);
		}*/
	}

	void print_spreadsheet(){
		printf("%s\n", "-- Print spreadhsheet --");
		for(int i=0; i<rows; ++i){
			for(int j=0; j<cols; ++j){
				printf("%d ", arr_spread[i][j]);
			}
			printf("\n");
		}
	}

	int get_column(){
		return 0;
	}

	~spreadhsheet(){
		//printf("%s\n", "Destructor called");
		for(int i=0; i<rows; ++i){
			delete[] arr_spread[i];
		}
		delete[] arr_spread;
	}

};

int main(){
	int num_spreadsheet = 0;
	int cols = 0 , rows = 0;
	scanf("%d",&num_spreadsheet);
	for(int i=0; i<num_spreadsheet; ++i){
		scanf("%d %d",&cols, &rows);
		spreadhsheet sp(rows, cols);
		sp.input_values();
		sp.print_formulas();
		sp.print_spreadsheet();
	}

	return 0;
}