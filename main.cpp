#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <locale>
#include <string>
#include <vector>

using std::wcout;
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::ifstream;
using std::wofstream;
using std::vector;
using std::wstring;

int main(){
	setlocale(LC_ALL, "chs");

	// Get source page
	vector<char> page_data;
	string page_path;
	ifstream page_file;
	long long page_file_size;

	cout << "试卷路径: ";
	cin >> page_path;
	page_file.open(page_path, std::ios_base::binary);
	if(!page_file.is_open()){
		system("cls");
		cout << "打开文件失败" << endl;
		return 0;
	}
	
	// Decode data
	page_file_size = page_file.seekg(0, std::ios_base::end).tellg();
	page_data.resize(page_file_size);
	page_file.seekg(std::ios_base::beg).read(page_data.data(), page_file_size);
	for(auto& data : page_data){
		if(data != 0){
			if(data != -27){
				data ^= 0xE5;
			}
		}
	}

	// Convert page and show
	wstring page_wchar_data;
	FILE* file = fopen("out.txt", "w+");

	auto* wdata = reinterpret_cast<wchar_t*>(page_data.data());
	for(int i = page_file_size / 2;i >= 0;i--){
		if(*wdata != '\0'){
			page_wchar_data.push_back(*wdata);
		}else{
			if(!page_wchar_data.empty()){
				printf("%ls\n", page_wchar_data.c_str());
				fprintf(file, "%ls\n", page_wchar_data.c_str());
				page_wchar_data.clear();
			}
		}
		wdata++;
	}

	fclose(file);
	system("pause");
	return 0;
}