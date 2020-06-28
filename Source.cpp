#include <iostream>
#include <sstream>
#include <string>
#include <cctype>

using namespace std;

void input_mat(int index);
void print_mat(char mat_name);
void add(char first, char second, char third);
void sub(char first, char second, char third);
void mult(char first, char second, char third, bool division);
void div(char first, char second, char third);
void cofactor(char first, int r, int c);
float det(char first);
void adj(char first);
void inv(char first);
void trans(char first, char second, bool division);
int mat_num = 0, temp_num = 900, next_temp = 0, mat_index;
bool new_mat = true, close = false;
string input;
stringstream ss;
pair<char, int> names[20000];
pair<char, int> rows[20000];
pair<char, int> columns[20000];
float mat[20000][100][100];

int main() {
    while (!close) {
        getline(cin, input);
        if (input == "exit") {
            close = true;
        }
        else if (input.length() == 1) {
            print_mat(input[0]);
        }
        else if (input[4] == '[') {
            new_mat = true;
            for (int i = 0; i < 20000; i++) {
                if (names[i].first == input[0]) {
                    mat_index = i;
                    new_mat = false;
                    input_mat(mat_index);
                    break;
                }
            }
            if (new_mat) {
                mat_index = mat_num;
                names[mat_num].first = input[0];
                rows[mat_num].first = input[0];
                columns[mat_num].first = input[0];
                names[mat_num].second = mat_index;
                input_mat(mat_index);
                mat_num++;
            }
        }
        else if (input.length() == 9 && !isdigit(input[4])) {
            switch (input[6])
            {
            case '+':
                add(input[4], input[8], input[0]);
                break;
            case '-':
                sub(input[4], input[8], input[0]);
                break;
            case '*':
                mult(input[4], input[8], input[0], 0);
                print_mat(input[0]);
                break;
            }
        }
        else if (input[5] == '/' && isalpha(input[4]) && isalpha(input[6])) {
            div(input[4], input[6], input[0]);
        }
        else if (input[5] == '\'' && isalpha(input[4])) {
            trans(input[4], input[0], 0);
            print_mat(input[0]);
        }
        else if (input.empty()) {
            cout << "Please enter the input exactly as specified in the PDF" << endl << "Spaces are important";
        }
    }
	return 0;
}
void input_mat(int index) {
    int row = 1, column = 1;
    for (int i = 4; i < input.length(); i++) {
        if (input[i] == ';') {
            row++;
        }
    }
    for (int i = 4; input[i] != ';' && i < input.length(); i++) {
        if (input[i] == ' ') {
            column++;
        }
    }
    rows[index].second = row;
    columns[index].second = column;
    input.insert(5, " ");
    ss << input;
    string word;
    float number;
    int i = 0, j = 0;
    while (!ss.eof()) {
        ss >> word;
        if (stringstream(word) >> number) {
            mat[index][i][j] = number;
            j++;
            if (j == column) {
                j = 0;
                i++;
            }
        }
    }
    ss.clear();
}
void print_mat(char mat_name) {
    int where;
    int colon = 1;
    bool found = false;
    for (int i = 0; i < 20000; i++) {
        if (names[i].first == mat_name) {
            where = i;
            found = true;
            break;
        }
    }
    if (found) {
        cout << names[where].first << " = [";
        for (int i = 0; i < rows[where].second; i++) {
            for (int j = 0; j < columns[where].second; j++) {
                cout << mat[where][i][j];
                if (j < columns[where].second - 1) {
                    cout << ' ';
                }
            }
            if (colon < rows[where].second) {
                cout << "; ";
                colon++;
            }
        }
        cout << ']' << endl;
    }
    else {
        cout << "Matrix " << mat_name << " hasn't been defined yet" << endl;
    }
}
void add(char first, char second, char third) {
    int first_index, second_index, third_index;
    bool found = false, f1 = false, f2 = false;
    for (int i = 0; i < 20000; i++) {
        if (names[i].first == first && f1 == false) {
            first_index = i;
            f1 = true;
        }
        else if (names[i].first == second && f2 == false) {
            second_index = i;
            f2 = true;
        }
        else if (names[i].first == third && found == false) {
            third_index = i;
            found = true;
        }
    }
    if (f1 == false) {
        cout << "Matrix " << first << " is not defined";
        return;
    }
    if (f2 == false) {
        cout << "Matrix " << second << " is not defined";
        return;
    }
    if (rows[first_index].second != rows[second_index].second || columns[first_index].second != columns[second_index].second) {
        cout << "The two matrices are not of the same size" << endl;
        return;
    }
    else {
        if (found) {
            rows[third_index].second = rows[first_index].second;
            columns[third_index].second = columns[first_index].second;
            for (int i = 0; i < rows[first_index].second; i++) {
                for (int j = 0; j < columns[first_index].second; j++) {
                    mat[third_index][i][j] = mat[first_index][i][j] + mat[second_index][i][j];
                }
            }
        }
        else {
            names[mat_num].first = input[0];
            rows[mat_num].first = input[0];
            columns[mat_num].first = input[0];
            rows[mat_num].second = rows[first_index].second;
            columns[mat_num].second = columns[first_index].second;
            for (int i = 0; i < rows[first_index].second; i++) {
                for (int j = 0; j < columns[first_index].second; j++) {
                    mat[mat_num][i][j] = mat[first_index][i][j] + mat[second_index][i][j];
                }
            }
            mat_num++;
        }
    }
    print_mat(third);
}
void sub(char first, char second, char third) {
    int first_index, second_index, third_index;
    bool found = false, f1 = false, f2 = false;
    for (int i = 0; i < 20000; i++) {
        if (names[i].first == first && f1 == false) {
            first_index = i;
            f1 = true;
        }
        else if (names[i].first == second && f2 == false) {
            second_index = i;
            f2 = true;
        }
        else if (names[i].first == third && found == false) {
            third_index = i;
            found = true;
        }
    }
    if (f1 == false) {
        cout << "Matrix " << first << " is not defined";
        return;
    }
    if (f2 == false) {
        cout << "Matrix " << second << " is not defined";
        return;
    }
    if (rows[first_index].second != rows[second_index].second || columns[first_index].second != columns[second_index].second) {
        cout << "The two matrices are not of the same size" << endl;
        return;
    }
    else {
        if (found) {
            rows[third_index].second = rows[first_index].second;
            columns[third_index].second = columns[first_index].second;
            for (int i = 0; i < rows[first_index].second; i++) {
                for (int j = 0; j < columns[first_index].second; j++) {
                    mat[third_index][i][j] = mat[first_index][i][j] - mat[second_index][i][j];
                }
            }
        }
        else {
            names[mat_num].first = input[0];
            rows[mat_num].first = input[0];
            columns[mat_num].first = input[0];
            rows[mat_num].second = rows[first_index].second;
            columns[mat_num].second = columns[first_index].second;
            for (int i = 0; i < rows[first_index].second; i++) {
                for (int j = 0; j < columns[first_index].second; j++) {
                    mat[mat_num][i][j] = mat[first_index][i][j] - mat[second_index][i][j];
                }
            }
            mat_num++;
        }
    }
    print_mat(third);
}
void mult(char first, char second, char third, bool division) {
    int first_index, second_index, third_index;
    bool found = false, f1 = false, f2 = false;
    for (int i = 0; i < 20000; i++) {
        if (names[i].first == first && f1 == false) {
            first_index = i;
            f1 = true;
        }
        else if (names[i].first == second && f2 == false) {
            second_index = i;
            f2 = true;
        }
        else if (names[i].first == third && found == false) {
            third_index = i;
            found = true;
        }
    }
    if (f1 == false) {
        cout << "Matrix " << first << " is not defined";
        return;
    }
    if (f2 == false) {
        cout << "Matrix " << second << " is not defined";
        return;
    }
    if (division) {
        second_index = 19999;
    }
    if (columns[first_index].second != rows[second_index].second) {
        cout << "The two matrices can't be multiplied in this order" << endl;
        return;
    }
    else {
        if (found) {
            rows[third_index].second = rows[first_index].second;
            columns[third_index].second = columns[second_index].second;
            for (int i = 0; i < rows[third_index].second; i++) {
                for (int j = 0; j < columns[third_index].second; j++) {
                    mat[third_index][i][j] = 0;
                }
            }
            for (int k = 0; k < rows[first_index].second; k++) {
                for (int j = 0; j < columns[second_index].second; j++) {
                    for (int i = 0; i < columns[first_index].second; i++) {
                        mat[third_index][k][j] += mat[first_index][k][i] * mat[second_index][i][j];
                    }
                }
            }
        }
        else {
            names[mat_num].first = input[0];
            rows[mat_num].first = input[0];
            columns[mat_num].first = input[0];
            rows[mat_num].second = rows[first_index].second;
            columns[mat_num].second = columns[second_index].second;
            for (int k = 0; k < rows[first_index].second; k++) {
                for (int j = 0; j < columns[second_index].second; j++) {
                    for (int i = 0; i < columns[first_index].second; i++) {
                        mat[mat_num][k][j] += mat[first_index][k][i] * mat[second_index][i][j];
                    }
                }
            }
            mat_num++;
        }
    }
}
void div(char first, char second, char third) {
    int first_index, second_index, third_index;
    bool found = false, f1 = false, f2 = false;
    for (int i = 0; i < 20000; i++) {
        if (names[i].first == first && f1 == false) {
            first_index = i;
            f1 = true;
        }
        else if (names[i].first == second && f2 == false) {
            second_index = i;
            f2 = true;
        }
        else if (names[i].first == third && found == false) {
            third_index = i;
            found = true;
        }
    }
    if (f1 == false) {
        cout << "Matrix " << first << " is not defined";
        return;
    }
    if (f2 == false) {
        cout << "Matrix " << second << " is not defined";
        return;
    }
    if (found) {
        rows[third_index].second = rows[first_index].second;
        columns[third_index].second = columns[second_index].second;
        inv(second);
        mult(first, '&', third, 1);
        print_mat(third);
    }
    else {
        names[mat_num].first = input[0];
        rows[mat_num].first = input[0];
        columns[mat_num].first = input[0];
        rows[mat_num].second = rows[first_index].second;
        columns[mat_num].second = columns[second_index].second;
        inv(second);
        mult(first, '&', third, 1);
        print_mat(third);
        mat_num++;
    }
}
void trans(char first, char second, bool division) {
    int first_index, second_index;
    bool found = false, f1  = false;
    for (int i = 0; i < 20000; i++) {
        if (names[i].first == first && f1 == false) {
            first_index = i;
            f1 = true;
        }
        else if (names[i].first == second && found == false) {
            second_index = i;
            found = true;
        }
    }
    if (division) {
        first_index = 19998;
        second_index = 19997;
    }
    if (found) {
        rows[second_index].second = columns[first_index].second;
        columns[second_index].second = columns[first_index].second;
        for (int i = 0; i < rows[first_index].second; i++) {
            for (int j = 0; j < columns[first_index].second; j++) {
                mat[second_index][j][i] = mat[first_index][i][j];
            }
        }
    }
    else {
        names[mat_num].first = input[0];
        rows[mat_num].first = input[0];
        columns[mat_num].first = input[0];
        rows[mat_num].second = columns[first_index].second;
        columns[mat_num].second = rows[first_index].second;
        for (int i = 0; i < rows[first_index].second; i++) {
            for (int j = 0; j < columns[first_index].second; j++) {
                mat[mat_num][j][i] = mat[first_index][i][j];
            }
        }
        mat_num++;
    }
}
void cofactor(char first, int r, int c) {
    int first_index, k = 0, l = 0;
    for (int i = 0; i < 20000; i++) {
        if (names[i].first == first) {
            first_index = i;
            break;
        }
    }
    names[temp_num].first = '#' + next_temp;
    rows[temp_num].first = '#' + next_temp;
    columns[temp_num].first = '#' + next_temp;
    rows[temp_num].second = rows[first_index].second - 1;
    columns[temp_num].second = columns[first_index].second - 1;
    for (int i = 0; i < rows[first_index].second; i++) {
        for (int j = 0; j < columns[first_index].second; j++) {
            if (j != c && i != r) {
                mat[temp_num][k][l] = mat[first_index][i][j];
                l++;
            }
        }
        if (l == columns[first_index].second - 1) {
            k++;
            l = 0;
        }
    }
}
float det(char first) {
    int first_index, s = 1;
    float sum = 0;
    for (int i = 0; i < 20000; i++) {
        if (names[i].first == first) {
            first_index = i;
            break;
        }
    }
    if (rows[first_index].second != columns[first_index].second) {
        cout << "Matrix " << first << "must be a square matrix" << endl;
        return 0;
    }
    if (rows[first_index].second == 1) {
        return mat[first_index][0][0];
    }
    for (int i = 0; i < columns[first_index].second; i++) {
        cofactor(first, 0, i);
        next_temp++;
        temp_num++;
        sum += s * mat[first_index][0][i] * det('#' + next_temp - 1);
        s *= -1;
    }
    return sum;
}
void adj(char first) {
    int first_index, s;
    for (int i = 0; i < 20000; i++) {
        if (names[i].first == first) {
            first_index = i;
            break;
        }
    }
    temp_num = 900;
    next_temp = 0;
    for (int i = 0; i < rows[first_index].second; i++) {
        for (int j = 0; j < columns[first_index].second; j++) {
            cofactor(first, i, j);
            temp_num++;
            next_temp++;
            if ((i + j) % 2 == 0) {
                s = 1;
            }
            else {
                s = -1;
            }
            mat[19998][i][j] = s * det('#' + next_temp - 1);
        }
        names[19998].first = '$';
        rows[19998].first = '$';
        columns[19998].first = '$';
        names[19997].first = '@';
        rows[19997].first = '@';
        columns[19997].first = '@';
        rows[19998].second = rows[first_index].second;
        columns[19998].second = columns[first_index].second;
    }
}
void inv(char first) {
    int first_index;
    temp_num = 900;
    next_temp = 0;
    float determ = det(first);
    if (determ == 0) {
        cout << "Matrix " << first << " has no inverse" << endl;
    }
    else {
        for (int i = 0; i < 20000; i++) {
            if (names[i].first == first) {
                first_index = i;
                break;
            }
        }
        adj(first);
        trans('$', '@', 1);
        for (int i = 0; i < rows[first_index].second; i++) {
            for (int j = 0; j < columns[first_index].second; j++) {
                mat[19999][i][j] = mat[19997][i][j] / determ;
            }
        }
        names[19999].first = '&';
        rows[19999].first = '&';
        columns[19999].first = '&';
        rows[19999].second = rows[first_index].second;
        columns[19999].second = columns[first_index].second;
    }
}