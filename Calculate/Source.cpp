#include <iostream>
#include <string>
#include <windows.h>
#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;
template<typename T>
T control_per(bool type = false, bool flag = false)
{
	char per[100];
	gets_s(per);
	int kol_t = 0;
	T result;
	while (strlen(per) == 0)
	{
		printf("Введено некорректное значение. Повторите попытку: ");
		gets_s(per);
	}
	for (int i = 0; i < strlen(per); i++)
	{
		if (int(per[0]) == 45 && flag == true) i++;
		if (int(per[i]) == 46 && type == true)
		{
			kol_t++;
			i++;
		}
		if (int(per[i]) < 48 || int(per[i]) > 57 || (type == true && kol_t > 1))
		{
			printf("Введено некорректное значение. Повторите попытку: ");
			gets_s(per);
			kol_t = 0;
			while (strlen(per) == 0)
			{
				printf("Введено некорректное значение. Повторите попытку: ");
				gets_s(per);
			}
			i = -1;
		}
	}
	if (type == true) result = atof(per);
	else result = atoi(per);
	return result;
}
int read_int()
{
	char per[100] = { 0 };
	gets_s(per);
	while (strlen(per) == 0)
	{
		printf("Введено некорректное значение. Повторите попытку: ");
		gets_s(per);
	}
	for (int i = 0; i < strlen(per); i++)
	{
		if ((per[i]) < '0' || per[i] > '9')
		{
			printf("Введено некорректное значение. Повторите попытку: ");
			gets_s(per);
			while (strlen(per) == 0)
			{
				printf("Введено некорректное значение. Повторите попытку: ");
				gets_s(per);
			}
			i = -1;
		}
	}
	int result = atoi(per);
	return result;
}
void mult_delete(string& math)
{
	for (int i = 1; i < math.size(); i++)
	{
		if (((math[i - 1] >= '0' && math[i - 1] <= '9') && math[i] == '*' && ((math[i + 1] > '@' && math[i + 1] < '[') || (math[i + 1] > '`' && math[i + 1] < '{'))) || (((math[i - 1] > '@' && math[i - 1] < '[') || (math[i - 1] > '`' && math[i - 1] < '{')) && math[i] == '*' && ((math[i + 1] > '@' && math[i + 1] < '[') || (math[i + 1] > '`' && math[i + 1] < '{'))))
		{
			math.erase(i, 1);
			i--;
		}
	}
}
void razvorot_chisla(string& point_obr, string& point1)
{
	if (point_obr.size() == 1) point1 = point_obr;
	else //
	{
		for (int k = point_obr.size() - 1; k >= 0; k--)
		{
			point1.push_back(point_obr[k]);
		}
	}
}
void processing_zamena(string& math, int start, int end, string result_s, double result)
{
	math.erase(math.begin() + start, math.begin() + end); //
	result_s = to_string(result);
	if (result == int(result)) result_s.erase(result_s.begin() + result_s.find('.'), result_s.end());
	math.insert(start, result_s);
}
void process_mult_div(string& math)
{
	string mathematic_operation, point1, point2, result_s, point_obr;
	int start, end, kol = 0, znak;
	double per1, per2, result;
	for (int i = 0; i < math.size(); i++)
	{
		if ((math[i] == '*') || (math[i] == '/'))
		{
			znak = i;
			i--;
			while ((math[i] >= '0' && math[i] <= '9') || math[i] == '.' || (math[i] == '-' && i == 0) || (math[i] == '-' && (math[i - 1] < '0' && math[i - 1] > '9')))
			{
				point_obr += math[i];
				if (i == 0) break;
				i--;
				kol++;
			}
			razvorot_chisla(point_obr, point1);
			if (i == 0) start = 0;
			else start = i + 1;
			for (int j = 0; j <= kol + 1; j++)
			{
				i++;
			}
			while ((math[i] >= '0' && math[i] <= '9') || math[i] == '.' || (math[i] == '*' && math[i + 1] == '-') || (math[i] == '-' && math[i - 1] == '*') || (math[i] == '-' && math[i - 1] == '/'))
			{
				point2 += math[i];
				i++;
			}
			end = i;
			per1 = stod(point1);
			per2 = stod(point2);
			if (math[znak] == '*') result = per1 * per2;
			else if (math[znak] == '/') result = per1 / per2;
			processing_zamena(math, start, end, result_s, result);
			point_obr.clear();
			point1.clear();
			point2.clear();
			i--;
			kol = 0;
			i = start;
		}
	}
}
void minus_minus_to_plus(string& mathematic_operation)
{
	for (int i = 0; i < mathematic_operation.size(); i++) //
	{
		if (mathematic_operation[i] == '-' && mathematic_operation[i + 1] == '-')
		{
			mathematic_operation.erase(i, 1);
			mathematic_operation[i] = '+';
			i = 0;
		}
	}
}
void process_plus_minus(string& mathematic_operation, double& result)
{
	string point, znak;
	bool flag = false;
	minus_minus_to_plus(mathematic_operation);
	for (int i = 0; i < mathematic_operation.size(); i++)
	{
		if (flag == false)
		{
			if ((mathematic_operation[i] >= '0' && mathematic_operation[i] <= '9') || mathematic_operation[i] == '.')
			{
				while ((mathematic_operation[i] >= '0' && mathematic_operation[i] <= '9') || mathematic_operation[i] == '.')
				{
					point += mathematic_operation[i];
					i++;
				}
				result += stod(point);
			}
			flag = true;
		}
		point.clear();
		if (mathematic_operation[i] == '*' || mathematic_operation[i] == '+' || mathematic_operation[i] == '-' || mathematic_operation[i] == '/')
		{
			znak = mathematic_operation[i];
		}
		if ((mathematic_operation[i] >= '0' && mathematic_operation[i] <= '9') || mathematic_operation[i] == '.')
		{
			while ((mathematic_operation[i] >= '0' && mathematic_operation[i] <= '9') || mathematic_operation[i] == '.')
			{
				point += mathematic_operation[i];
				if (mathematic_operation[i + 1] == '.') {}
				else if (mathematic_operation[i + 1] < '0' || mathematic_operation[i + 1] > '9') break;
				i++;
			}
			if (znak == "+") result += stod(point);
			else if (znak == "-") result -= stod(point);
		}
	}

}
void obrabotka_skobok(bool multi_del_check, string& skobki, double& result, string& math, int start, int end, string& result_s, int& i)
{
	if (multi_del_check == true) process_mult_div(skobki);
	process_plus_minus(skobki, result);
	math.erase(math.begin() + start, math.begin() + end);
	result_s = to_string(result);
	math.insert(start, result_s);
	skobki.clear();
	i = start;
	result = 0;
}
void kopirovanie_skobka(int& start, int& i, string& math, string& skobki, bool& multi_del_check, bool& skobka_v_skobke)
{
	start = i;
	i++;
	while (math[i] != ')')
	{
		skobki += math[i];
		if (math[i] == '*' || math[i] == '/') multi_del_check = true;
		if (math[i] == '(') skobka_v_skobke = true;
		i++;
	}
}
void skobki_v_skobke_correct(string& skobki, bool& skobki_check, int& start2, int& end2, string& skobki2, bool& multi_del_check2, bool& skobka_v_skobke2)
{
	for (int i = 0; i < skobki.size(); i++)
	{
		if (skobki[i] == '(')
		{
			skobki_check = true;
			kopirovanie_skobka(start2, i, skobki, skobki2, multi_del_check2, skobka_v_skobke2);
			if (skobka_v_skobke2 == true)
			{
				while (skobki[i] == ')' && (i != skobki.size() - 1 || skobki[i + 1] == ')'))
				{
					skobki2 += ")";
					i++;
				}
			}
			end2 = i + 1;
		}
	}
}
void skobki_correct(string& math)
{
	int start = 0, end = 0, start2 = 0, end2 = 0;
	double result = 0, result2 = 0;
	bool multi_del_check = false, multi_del_check2 = false, skobki_check = false, skobka_v_skobke = false, skobka_v_skobke2 = false, check = false;
	string skobki, result_s, skobki2;
	for (int i = 0; i < math.size(); i++)
	{
		if (math[i] == '(')
		{
			kopirovanie_skobka(start, i, math, skobki, multi_del_check, skobka_v_skobke);
			if (skobka_v_skobke == true)
			{
				while (math[i] == ')' && math[i + 1] == ')')
				{
					skobki += ")";
					i++;
				}
				while (math[i] == ')' && (math[i + 1] == '+' || math[i + 1] == '-' || math[i + 1] == '*' || math[i + 1] == '/'))
				{
					skobki += ")";
					i++;
					check = true;
				}
			}
			if (check != true) end = i + 1;
			else end = i;
			skobki_v_skobke_correct(skobki, skobki_check, start2, end2, skobki2, multi_del_check2, skobka_v_skobke2);
			if (skobki_check == true)
			{
				skobki_correct(skobki2);
				skobki_check = false;
				obrabotka_skobok(multi_del_check2, skobki2, result2, skobki, start2, end2, result_s, i);

			}
			obrabotka_skobok(multi_del_check, skobki, result, math, start, end, result_s, i);
		}
	}
}
bool check(string& math);
bool not_empty_skobki(string math, int i)
{
	if (math[i] == '(' && math[i + 1] == ')')
	{
		cout << "В математической задаче допущена ошибка: пустые скобки." << endl;
		return false;
	}
	return true;
}

bool cmath_obrabotka(string& math, int& i, string& abs_operation, int& end)
{
	int kol_otkr_sk = 0, kol_zakr_sk = 0;
	if (!(not_empty_skobki(math, i))) return false;
	i++;
	while (true)
	{
		if (math[i] == '(') kol_otkr_sk++;
		if (math[i] == ')') kol_zakr_sk++;
		if (kol_otkr_sk != kol_zakr_sk - 1)
		{
			abs_operation += math[i];
			i++;
			if (i == math.size() || math[math.size() - 1] == '(')
			{
				cout << "В математической задаче допущена ошибка: количество открытых скобок не равно количеству закрытых скобок." << endl;
				return false;
			}
		}
		else
		{
			i++;
			break;
		}
	}
	if (abs_operation.size() == 1 && abs_operation[0] == ',')
	{
		cout << "В математической задаче допущена ошибка: математическая функция без параметров." << endl;
		return false;
	}
	end = i;
	return true;
}
bool get_parametr_of_matmematic_function(string& first, double& point1)
{
	first.erase(remove(begin(first), end(first), ' '), end(first));
	if (!check(first)) return false;
	skobki_correct(first);
	process_mult_div(first);
	process_plus_minus(first, point1);
}
bool cmath_vstavka_result(string& math, int& i, string& operation, double& answer, int start, int end, double (*function)(double))
{
	if (!get_parametr_of_matmematic_function(operation, answer)) return false;
	answer = function(answer);
	processing_zamena(math, start, end, operation, answer);
	i = start;
	return true;
}
bool cmath_vstavka_result(string& math, int& i, string& operation, double& answer, int start, int end, int zap_index, double (*function)(double, double))
{
	double point1 = 0, point2 = 0;
	string first, second;
	for (int i = 0; i < zap_index; i++)
	{
		first += operation[i];
	}
	for (int i = zap_index + 1; i < operation.size(); i++)
	{
		second += operation[i];
	}
	if (!get_parametr_of_matmematic_function(first, point1)) return false;
	if (!get_parametr_of_matmematic_function(second, point2)) return false;
	answer = function(point1, point2);
	processing_zamena(math, start, end, operation, answer);
	i = start;
	return true;
}
bool abs_check(string& math, int& i)
{
	int start, end;
	double answer = 0;
	string operation;
	if ((math[i] == 'a' || math[i] == 'A') && (math[i + 1] == 'b' || math[i + 1] == 'B') && (math[i + 2] == 's' || math[i + 2] == 'S') && math[i + 3] == '(')
	{
		start = i;
		i += 3;
		if (!cmath_obrabotka(math, i, operation, end)) return false;
		if (!cmath_vstavka_result(math, i, operation, answer, start, end, &abs)) return false;
	}
	return true;
}
bool ceil_check(string& math, int& i)
{
	int start, end;
	double answer = 0;
	string operation;
	if ((math[i] == 'c' || math[i] == 'C') && (math[i + 1] == 'e' || math[i + 1] == 'E') && (math[i + 2] == 'i' || math[i + 2] == 'I') && (math[i + 3] == 'l' || math[i + 3] == 'L') && math[i + 4] == '(')
	{
		start = i;
		i += 4;
		if (!cmath_obrabotka(math, i, operation, end)) return false;
		if (!cmath_vstavka_result(math, i, operation, answer, start, end, &ceil)) return false;
	}
	return true;
}
bool round_check(string& math, int& i)
{
	int start, end;
	double answer = 0;
	string operation;
	if ((math[i] == 'r' || math[i] == 'R') && (math[i + 1] == 'o' || math[i + 1] == 'O') && (math[i + 2] == 'u' || math[i + 2] == 'U') && (math[i + 3] == 'n' || math[i + 3] == 'N') && (math[i + 4] == 'd' || math[i + 4] == 'D') && math[i + 5] == '(')
	{
		start = i;
		i += 5;
		if (!cmath_obrabotka(math, i, operation, end)) return false;
		if (!cmath_vstavka_result(math, i, operation, answer, start, end, &round)) return false;
	}
	return true;
}
bool floor_check(string& math, int& i)
{
	int start, end;
	double answer = 0;
	string operation;
	if ((math[i] == 'f' || math[i] == 'F') && (math[i + 1] == 'l' || math[i + 1] == 'L') && (math[i + 2] == 'o' || math[i + 2] == 'O') && (math[i + 3] == 'o' || math[i + 3] == 'O') && (math[i + 4] == 'r' || math[i + 4] == 'R') && math[i + 5] == '(')
	{
		start = i;
		i += 5;
		if (!cmath_obrabotka(math, i, operation, end)) return false;
		if (!cmath_vstavka_result(math, i, operation, answer, start, end, &floor)) return false;
	}
	return true;
}
bool trunc_check(string& math, int& i)
{
	int start, end;
	double answer = 0;
	string operation;
	if ((math[i] == 't' || math[i] == 'T') && (math[i + 1] == 'r' || math[i + 1] == 'R') && (math[i + 2] == 'u' || math[i + 2] == 'U') && (math[i + 3] == 'n' || math[i + 3] == 'N') && (math[i + 4] == 'c' || math[i + 4] == 'C') && math[i + 5] == '(')
	{
		start = i;
		i += 5;
		if (!cmath_obrabotka(math, i, operation, end)) return false;
		if (!cmath_vstavka_result(math, i, operation, answer, start, end, &trunc)) return false;
	}
	return true;
}
bool cbrt_check(string& math, int& i)
{
	int start, end;
	double answer = 0;
	string operation;
	if ((math[i] == 'c' || math[i] == 'C') && (math[i + 1] == 'b' || math[i + 1] == 'B') && (math[i + 2] == 'r' || math[i + 2] == 'R') && (math[i + 3] == 't' || math[i + 3] == 'T') && math[i + 4] == '(')
	{
		start = i;
		i += 4;
		if (!cmath_obrabotka(math, i, operation, end)) return false;
		if (!cmath_vstavka_result(math, i, operation, answer, start, end, &cbrt)) return false;
	}
	return true;
}
bool sqrt_check(string& math, int& i)
{
	int start, end;
	double answer = 0;
	string operation;
	if ((math[i] == 's' || math[i] == 'S') && (math[i + 1] == 'q' || math[i + 1] == 'Q') && (math[i + 2] == 'r' || math[i + 2] == 'R') && (math[i + 3] == 't' || math[i + 3] == 'T') && math[i + 4] == '(')
	{
		start = i;
		i += 4;
		if (!cmath_obrabotka(math, i, operation, end)) return false;
		if (!cmath_vstavka_result(math, i, operation, answer, start, end, &sqrt)) return false;
	}
	return true;
}
bool exp_check(string& math, int& i)
{
	int start, end;
	double answer = 0;
	string operation;
	if ((math[i] == 'e' || math[i] == 'E') && (math[i + 1] == 'x' || math[i + 1] == 'X') && (math[i + 2] == 'p' || math[i + 2] == 'P') && math[i + 3] == '(')
	{
		start = i;
		i += 3;
		if (!cmath_obrabotka(math, i, operation, end)) return false;
		if (!cmath_vstavka_result(math, i, operation, answer, start, end, &exp)) return false;
	}
	return true;
}
bool log_check(string& math, int& i)
{
	int start, end;
	double answer = 0;
	string operation;
	if ((math[i] == 'l' || math[i] == 'L') && (math[i + 1] == 'o' || math[i + 1] == 'O') && (math[i + 2] == 'g' || math[i + 2] == 'G') && math[i + 3] == '(')
	{
		start = i;
		i += 3;
		if (!cmath_obrabotka(math, i, operation, end)) return false;
		if (!cmath_vstavka_result(math, i, operation, answer, start, end, &log)) return false;
	}
	return true;
}
bool log10_check(string& math, int& i)
{
	int start, end;
	double answer = 0;
	string operation;
	if ((math[i] == 'l' || math[i] == 'L') && (math[i + 1] == 'o' || math[i + 1] == 'O') && (math[i + 2] == 'g' || math[i + 2] == 'G') && math[i + 3] == '1' && math[i + 4] == '0' && math[i + 5] == '(')
	{
		start = i;
		i += 5;
		if (!cmath_obrabotka(math, i, operation, end)) return false;
		if (!cmath_vstavka_result(math, i, operation, answer, start, end, &log10)) return false;
	}
	return true;
}
bool sin_check(string& math, int& i)
{
	int start, end;
	double answer = 0;
	string operation;
	if ((math[i] == 's' || math[i] == 'S') && (math[i + 1] == 'i' || math[i + 1] == 'I') && (math[i + 2] == 'n' || math[i + 2] == 'N') && math[i + 3] == '(')
	{
		start = i;
		i += 3;
		if (!cmath_obrabotka(math, i, operation, end)) return false;
		if (!cmath_vstavka_result(math, i, operation, answer, start, end, &sin)) return false;
	}
	return true;
}
bool cos_check(string& math, int& i)
{
	int start, end;
	double answer = 0;
	string operation;
	if ((math[i] == 'c' || math[i] == 'C') && (math[i + 1] == 'o' || math[i + 1] == 'O') && (math[i + 2] == 's' || math[i + 2] == 'S') && math[i + 3] == '(')
	{
		start = i;
		i += 3;
		if (!cmath_obrabotka(math, i, operation, end)) return false;
		if (!cmath_vstavka_result(math, i, operation, answer, start, end, &cos)) return false;
	}
	return true;
}
bool asin_check(string& math, int& i)
{
	int start, end;
	double answer = 0;
	string operation;
	if ((math[i] == 'a' || math[i] == 'A') && (math[i + 1] == 's' || math[i + 1] == 'S') && (math[i + 2] == 'i' || math[i + 2] == 'I') && (math[i + 3] == 'n' || math[i + 3] == 'N') && math[i + 4] == '(')
	{
		start = i;
		i += 4;
		if (!cmath_obrabotka(math, i, operation, end)) return false;
		if (!cmath_vstavka_result(math, i, operation, answer, start, end, &asin)) return false;
	}
	return true;
}
bool acos_check(string& math, int& i)
{
	int start, end;
	double answer = 0;
	string operation;
	if ((math[i] == 'a' || math[i] == 'A') && (math[i + 1] == 'c' || math[i + 1] == 'C') && (math[i + 2] == 'o' || math[i + 2] == 'O') && (math[i + 3] == 's' || math[i + 3] == 'S') && math[i + 4] == '(')
	{
		start = i;
		i += 4;
		if (!cmath_obrabotka(math, i, operation, end)) return false;
		if (!cmath_vstavka_result(math, i, operation, answer, start, end, &acos)) return false;
	}
	return true;
}
bool tan_check(string& math, int& i)
{
	int start, end;
	double answer = 0;
	string operation;
	if ((math[i] == 't' || math[i] == 'T') && (math[i + 1] == 'a' || math[i + 1] == 'A') && (math[i + 2] == 'n' || math[i + 2] == 'N') && math[i + 3] == '(')
	{
		start = i;
		i += 3;
		if (!cmath_obrabotka(math, i, operation, end)) return false;
		if (!cmath_vstavka_result(math, i, operation, answer, start, end, &tan)) return false;
	}
	return true;
}
bool atan_check(string& math, int& i)
{
	int start, end;
	double answer = 0;
	string operation;
	if ((math[i] == 'a' || math[i] == 'A') && (math[i + 1] == 't' || math[i + 1] == 'T') && (math[i + 2] == 'a' || math[i + 2] == 'A') && (math[i + 3] == 'n' || math[i + 3] == 'N') && math[i + 4] == '(')
	{
		start = i;
		i += 4;
		if (!cmath_obrabotka(math, i, operation, end)) return false;
		if (!cmath_vstavka_result(math, i, operation, answer, start, end, &atan)) return false;
	}
	return true;
}
bool pow_check(string& math, int& i);
bool zap_check_in_cmath(string operation, int zap, int zap_max, int& zap_index)
{
	bool function_in_function = false;
	for (int j = 0; j < operation.size(); j++)
	{
		pow_check(operation, j);
		if (zap == zap_max && operation[j] == ',')
		{
			cout << "В математической задаче допущена ошибка: некорректное задание математической функции." << endl;
			return false;
		}
		if (operation[j] == ',')
		{
			zap_index = j;
			zap++;
		}
	}
	if (zap == false)
	{
		cout << "В математической задаче допущена ошибка: некорректное задание математической функции." << endl;
		return false;
	}
	return true;
}
bool pow_check(string& math, int& i)
{
	int start, end, zap_index = 0, zap = 0, zap_max = 1;
	double answer = 0;
	string operation, first, second;
	if ((math[i] == 'p' || math[i] == 'P') && (math[i + 1] == 'o' || math[i + 1] == 'O') && (math[i + 2] == 'w' || math[i + 2] == 'W') && math[i + 3] == '(')
	{
		start = i;
		i += 3;
		if (!cmath_obrabotka(math, i, operation, end)) return false;
		if (!zap_check_in_cmath(operation, zap, zap_max, zap_index)) return false;
		if (!cmath_vstavka_result(math, i, operation, answer, start, end, zap_index, &pow)) return false;
	}
	return true;
}
bool binary_check(string math, int i)
{
	if (math[i] != '0' && math[i] != '1')
	{
		cout << "В математической задаче допущена ошибка: некорректное задание бинарного числа." << endl;
		return false;
	}
}
bool octal_check(string math, int i)
{
	if (math[i] != '0' && math[i] != '1' && math[i] != '2' && math[i] != '3' && math[i] != '4' && math[i] != '5' && math[i] != '6' && math[i] != '7')
	{
		cout << "В математической задаче допущена ошибка: некорректное задание восьмеричного числа." << endl;
		return false;
	}
}
bool hexadecimal_check(string math, int i)
{
	if (math[i] != '0' && math[i] != '1' && math[i] != '2' && math[i] != '3' && math[i] != '4' && math[i] != '5' && math[i] != '6' && math[i] != '7' && math[i] != '8' && math[i] != '9' && math[i] != 'A' && math[i] != 'B' && math[i] != 'C' && math[i] != 'D' && math[i] != 'E' && math[i] != 'F' && math[i] != 'a' && math[i] != 'b' && math[i] != 'c' && math[i] != 'd' && math[i] != 'e' && math[i] != 'f')
	{
		cout << "В математической задаче допущена ошибка: некорректное задание шестнадцатиричного числа." << endl;
		return false;
	}
}
bool sistema_chisl_copy(string& math, int& i, int& start, int& end, bool& odna_tochka, string& binary, int& binary_index, int& tochka_number, bool (*function)(string, int))
{
	start = i;
	i += 2;
	while (math[i] != '+' && math[i] != '-' && math[i] != '*' && math[i] != '/' && math[i] != ')')
	{
		if (math[i] == '.' && odna_tochka == false)
		{
			binary += math[i];
			odna_tochka = true;
			tochka_number = binary_index;
			i++;
		}
		if (!function(math, i)) return false;
		binary += math[i];
		if (i != math.size() - 1)
		{
			i++;
			binary_index++;
		}
		else
		{
			i++;
			break;
		}
	}
	if (odna_tochka == true)
	{
		binary.erase(tochka_number, 1);
		i--;
	}
	end = i;
}
void sistema_chisl_preobrazovanie(string& math, string& hexadecimal, double& hexadecimal_number, bool odna_tochka, int tochka_number, int value)
{
	for (int j = 0; j < hexadecimal.size(); j++)
	{
		if (odna_tochka == false)
		{
			if (isdigit(hexadecimal[j]))hexadecimal_number += ((int(hexadecimal[j]) - 48) * pow(value, hexadecimal.size() - 1 - j));
			else hexadecimal_number += ((int(hexadecimal[j]) - 55) * pow(value, hexadecimal.size() - 1 - j));
		}
		else
		{
			if (isdigit(hexadecimal[j]))hexadecimal_number += ((int(hexadecimal[j]) - 48) * pow(value, tochka_number - 1 - j));
			else hexadecimal_number += ((int(hexadecimal[j]) - 55) * pow(value, tochka_number - 1 - j));
		}
	}
}
bool binary_operation(string& math, int& i) //
{
	int start, end, tochka_number, binary_index = 0;
	double binary_number = 0;
	string binary, double_number;
	bool odna_tochka = false;
	if (math[i] == '0' && math[i + 1] == 'b' && math[i + 2] != '+' && math[i + 2] != '-' && math[i + 2] != '*' && math[i + 2] != '/')
	{
		if (!sistema_chisl_copy(math, i, start, end, odna_tochka, binary, binary_index, tochka_number, &binary_check)) return false;
		sistema_chisl_preobrazovanie(math, binary, binary_number, odna_tochka, tochka_number, 2);
		processing_zamena(math, start, end, double_number, binary_number);
		i = start;
	}
	return true;
}
bool octal_operation(string& math, int& i)
{
	int start, end, tochka_number, octal_index = 0;
	double octal_number = 0;
	string octal, double_number;
	bool odna_tochka = false;
	if (math[i] == '0' && math[i + 1] == 'o' && math[i + 2] != '+' && math[i + 2] != '-' && math[i + 2] != '*' && math[i + 2] != '/')
	{
		if (!sistema_chisl_copy(math, i, start, end, odna_tochka, octal, octal_index, tochka_number, &octal_check)) return false;
		sistema_chisl_preobrazovanie(math, octal, octal_number, odna_tochka, tochka_number, 8);
		processing_zamena(math, start, end, double_number, octal_number);
		i = start;
	}
	return true;
}
bool hexadecimal_operation(string& math, int& i)
{
	int start, end, tochka_number, hexadecimal_index = 0;
	double hexadecimal_number = 0;
	string hexadecimal, double_number;
	bool odna_tochka = false;
	if (math[i] == '0' && math[i + 1] == 'x' && math[i + 2] != '+' && math[i + 2] != '-' && math[i + 2] != '*' && math[i + 2] != '/')
	{
		if (!sistema_chisl_copy(math, i, start, end, odna_tochka, hexadecimal, hexadecimal_index, tochka_number, &hexadecimal_check)) return false;
		transform(hexadecimal.begin(), hexadecimal.end(), hexadecimal.begin(), toupper);
		sistema_chisl_preobrazovanie(math, hexadecimal, hexadecimal_number, odna_tochka, tochka_number, 16);
		processing_zamena(math, start, end, double_number, hexadecimal_number);
		i = start;
	}
	return true;
}
bool kolichectvo_skobok_check(string math)
{
	int skob_40 = 0, skob_41 = 0;
	for (int i = 0; i < math.size(); i++)
	{
		if (math[i] == '(') skob_40++;
		if (math[i] == ')') skob_41++;
	}
	if (skob_40 != skob_41)
	{
		cout << "В математической задаче допущена ошибка: количество открытых скобок не равно количеству закрытых скобок." << endl;
		return false;
	}
	return true;
}
bool division_by_zero(string math, int i)
{
	if (math[i] == '/' && math[i + 1] == '0' && math[i + 2] != '.')
	{
		cout << "В математической задаче допущена ошибка: деление на 0." << endl;
		return false;
	}
	return true;
}
bool number_after_alpha(string math, int i)
{
	if (((math[i] > '@' && math[i] < '[') || (math[i] > '`' && math[i] < '{')) && (math[i + 1] >= '0' && math[i + 1] <= '9'))
	{
		cout << "В математической задаче допущена ошибка: после буквы идет цифра." << endl;
		return false;
	}
	return true;
}
bool two_and_more_operators(string math, int i)
{
	if ((math[i] == '*' || math[i] == '+' || math[i] == '-' || math[i] == '.' || math[i] == '/') && (math[i + 1] == '*' || math[i + 1] == '+' || math[i + 1] == '-' || math[i + 1] == '.' || math[i + 1] == '/'))
	{
		cout << "В математической задаче допущена ошибка: два и более математических знака подряд." << endl;
		return false;
	}
	return true;
}
bool check2(string& math)
{
	for (int i = 0; i < math.size(); i++)
	{
		if ((math[i] == 'i' && math[i + 1] == 'n' && math[i + 2] == 'f') || (math[i] == '-' && math[i + 1] == 'n' && math[i + 2] == 'a' && math[i + 3] == 'n' && math[i + 4] == '(' && math[i + 5] == 'i' && math[i + 6] == 'n' && math[i + 7] == 'd' && math[i + 8] == ')'))
		{
			cout << "В математической задаче допущена ошибка: некорректное задание математического выражения." << endl;
			cout << "Повторите ввод: ";
			return false;
		}
	}
	return true;
}
bool unknown_symbol(string math, int i)
{
	if (!check2(math)) return false;
	//if (math[i] < '(' && math[i] > ' ' || math[i] == ',' || math[i] > '9')
	if (math[i] < '(' || math[i] == ',' || (math[i] > '9' && math[i] < 'A') || (math[i] > 'Z' && math[i] < 'a') || math[i] > 'z')
	{
		cout << "В математической задаче допущена ошибка: встречен недопустимый символ." << endl;
		return false;
	}
	return true;
}
bool invalid_character_combination(string math, int i)
{
	if ((math[i] == '(' && (math[i + 1] == '*' || math[i + 1] == '/')) || math[0] == '*' || math[0] == '/' || math[0] == '+')
	{
		cout << "В математической задаче допущена ошибка: недопустимое сочетание знаков." << endl;
		return false;
	}
	return true;
}
bool number_after_mathematic_operation(string math, int i)
{
	if ((math[i] == '*' || math[i] == '+' || math[i] == '-' || math[i] == '.' || math[i] == '/') && (math[i + 1] != '(' && (math[i + 1] < '0' || (math[i + 1] > '9' && math[i + 1] < 'A') || (math[i + 1] > 'Z' && math[i + 1] < 'a') || math[i + 1] > 'z')))
	{
		cout << "В математической задаче допущена ошибка: после математической операции обязательно должна идти цифра." << endl;
		return false;
	}
	return true;
}
bool operator_between_number_and_skobka(string math, int i)
{
	if ((math[i] >= '0' && math[i] <= '9' && math[i + 1] == '(') || (math[i] == ')' && math[i + 1] >= '0' && math[i + 1] <= '9'))
	{
		cout << "В математической задаче допущена ошибка: между цифрой и скобкой отсутствует математический оператор." << endl;
		return false;
	}
	return true;
}
bool tochki_check(string math)
{
	int kol_t = 0;
	for (int i = 0; i < math.size(); i++)
	{
		if (math[i] >= '0' && math[i] <= '9')
		{
			while ((math[i] >= '0' && math[i] <= '9') || (math[i] == '.'))
			{
				if (math[i] == '.')
				{
					kol_t++;
					if (kol_t > 1)
					{
						cout << "В математической задаче допущена ошибка: в вещественном числе точек больше, чем одна." << endl;
						return false;
					}
				}
				i++;
			}
			kol_t = 0;
		}
	}
	return true;
}
bool check(string& math)
{
	if (math.size() == 0)
	{
		cout << "В математической задаче допущена ошибка: пустое выражение" << endl;
		return false;
	}
	for (int i = 0; i < math.size(); i++)
	{
		if ((!pow_check(math, i)) || (!atan_check(math, i)) || (!tan_check(math, i)) || (!acos_check(math, i)) || (!asin_check(math, i)) || (!cos_check(math, i)) || (!sin_check(math, i)) || (!log10_check(math, i)) || (!log_check(math, i)) || (!exp_check(math, i)) || (!sqrt_check(math, i)) || (!cbrt_check(math, i)) || (!trunc_check(math, i)) || (!floor_check(math, i)) || (!round_check(math, i)) || (!ceil_check(math, i)) || (!abs_check(math, i)) || (!binary_operation(math, i)) || (!octal_operation(math, i)) || (!hexadecimal_operation(math, i)) || (!division_by_zero(math, i)) || (!unknown_symbol(math, i)) || (!two_and_more_operators(math, i)) || (!not_empty_skobki(math, i)) || (!invalid_character_combination(math, i)) || (!number_after_mathematic_operation(math, i)) || (!operator_between_number_and_skobka(math, i)) || (!number_after_alpha(math, i))) return false;
	}
	if ((!tochki_check(math)) || (!kolichectvo_skobok_check(math))) return false;
	return true;
}
struct Data
{
	string znak, number, per;
};
///////////////////////////////////////////////////////////////////////////////////////////
bool compare_symbols_of_per(string per1, string per2)
{
	bool check = false;
	if (per1.size() != per2.size()) return false;
	for (int i = 0; i < per1.size(); i++)
	{
		for (int j = 0; j < per2.size(); j++)
		{
			if (per1[i] == per2[j]) check = true;
		}
		if (check == false) return false;
		check = false;
	}
	return true;
}
void check_stepen_of_per(string& per)
{
	int kol = 0;
	string result;
	bool check = false;
	for (int x = 0; x < per.size(); x++)
	{
		kol++;
		result = "1";
		for (int y = x + 1; y < per.size(); y += result.size())
		{
			if (per[x] == per[y])
			{
				check = true;
				kol++;
				per.erase(y, 1);
				y--;

			}
		}
		if (check == true)
		{
			result = "^(" + to_string(kol) + ")";
			per.insert(x + 1, result);
			x += result.size();
			check = false;
		}
		kol = 0;
	}
}
void del_0_argument(vector<Data>& array)
{
	for (int i = 0; i < array.size(); i++)
	{
		if (array[i].number == "0")
		{
			array.erase(array.begin() + i);
			i--;
		}
	}
}
void plus_minus_per(vector<Data>& array)
{
	double number1, number2, result;
	for (int i = 0; i < array.size(); i++)
	{

		for (int j = i + 1; j < array.size(); j++)
		{
			if (compare_symbols_of_per(array[j].per, array[i].per))
				//if (array[j].per == array[i].per)
			{
				if ((array[j].znak == "+" || array[j].znak == "-") && (array[j].znak == "-" || array[j].znak == "+"))
				{
					number1 = stod(array[j].number);
					number2 = stod(array[i].number);
					if (array[j].znak == "+" && array[i].znak == "+") result = number1 + number2;
					else if (array[j].znak == "+" && array[i].znak == "-") result = number1 - number2;
					else if (array[j].znak == "-" && array[i].znak == "+") result = -number1 + number2;
					else if (array[j].znak == "-" && array[i].znak == "-") result = -number1 - number2;
					array[i].number = to_string(result);
					if (array[i].number[0] == '-')
					{
						array[i].number.erase(0, 1);
						array[i].znak = "-";
					}
					if (result == int(result)) array[i].number.erase(array[i].number.begin() + array[i].number.find('.'), array[i].number.end());
					array.erase(array.begin() + j);
					if (array[i].number == "0") array.erase(array.begin() + i);
					if (j == array.size() - 1)i--;
					else j--;
				}
			}
		}
	}
	del_0_argument(array);
}
void mult_del_check(string& math, vector<Data>& array)
{
	int index = 0, start = 0, end, index2;
	int kol_sk_40 = 0, kol_sk_41 = 0;
	bool check_number = false, check_mult_del = false;
	string point_obr, point_mult_del_1, point_mult_del_2;
	double answer = 0;
	for (int i = 0; i < math.size(); i++)
	{
		if ((math[i] > '@' && math[i] < '[') || (math[i] > '`' && math[i] < '{'))
		{
			index2 = i;
			while ((math[i + 1] > '@' && math[i + 1] < '[') || (math[i + 1] > '`' && math[i + 1] < '{'))
			{
				i++;
			}
			end = i + 1;
			if (math[end] == '*' || math[end] == '/')
			{
				check_mult_del = true;
				i++;
				point_mult_del_1 += math[i];
				i++;
				while (math[i] != '+' && math[i] != '-' && i != math.size())
				{
					point_mult_del_1 += math[i];
					i++;
					if (math[i] == '(')
					{
						kol_sk_40++;
						point_mult_del_1 += math[i];
						i++;
						while (kol_sk_40 != kol_sk_41)
						{
							point_mult_del_1 += math[i];
							if (math[i] == '(') kol_sk_40++;
							if (math[i] == ')') kol_sk_41++;
							i++;
						}
					}
				}
				end = i;
				i--;
				kol_sk_40 = 0, kol_sk_41 = 0;
			}
			i = index2;
			while (math[i] != '+' && math[i] != '-')
			{
				if (math[i] >= '0' && math[i] <= '9') check_number = true;
				point_obr += math[i];
				i--;
				if (i == -1)
				{
					i = 0;
					break;
				}
				if (math[i] == '*' || math[i] == '/')
				{
					check_mult_del = true;
					while (math[i] != '+' && math[i] != '-')
					{
						point_obr += math[i];
						i--;
						if (i == -1)
						{
							i = 0;
							break;
						}
						if (math[i] == '(')
						{
							kol_sk_40++;
							while (kol_sk_40 != kol_sk_41)
							{
								point_obr += math[i];
								if (math[i] == '(') kol_sk_40++;
								if (math[i] == ')') kol_sk_41++;
								i--;
								if (i == -1)
								{
									i = 0;
									break;
								}
							}
						}
					}
				}
				if (math[i] == '+' || math[i] == '-' || math[i] == '*' || math[i] == '/')
				{
					if (check_number == false)
					{
						point_obr += '1';
						point_obr += math[i];
						math.insert(math.begin() + i + 1, '1');
						end++;
						break;
					}
					point_obr += math[i];
					break;
				}
			}
			start = i;
			if (check_mult_del == false) break;
			razvorot_chisla(point_obr, point_mult_del_2);
			array.push_back(Data());
			point_mult_del_1 = point_mult_del_2 + point_mult_del_1;
			point_mult_del_2.clear();
			if (math[start] == '+' || math[start] == '-' || math[start] == '*' || math[start] == '/') array[index].znak = math[start];
			else array[index].znak = "+";
			for (int i = start; i < end; i++)
			{
				while ((math[i] >= '0' && math[i] <= '9') || math[i] == '.' || math[i] == '+' || math[i] == '-' || math[i] == '*' || math[i] == '/' || math[i] == '(' || math[i] == ')')
				{
					array[index].number += math[i];
					if (i < end - 1) i++;
					else break;
				}
				while ((math[i] > '@' && math[i] < '[') || (math[i] > '`' && math[i] < '{'))
				{
					array[index].per += math[i];
					if (i < end - 1) i++;
					else break;
				}
				if (i < end - 1) i--;
			}
			if (array[index].number[0] == '+' || array[index].number[0] == '-' || array[index].number[0] == '*' || array[index].number[0] == '/') array[index].number.erase(0, 1);
			point_obr.clear();
			transform(array[index].per.begin(), array[index].per.end(), array[index].per.begin(), tolower);
			if (array[index].number.empty()) array[index].number = "1";
			math.erase(math.begin() + start, math.begin() + end);
			skobki_correct(array[index].number);
			process_mult_div(array[index].number);
			process_plus_minus(array[index].number, answer);
			array[index].number = to_string(answer);
			if (answer == int(answer)) array[index].number.erase(array[index].number.begin() + array[index].number.find('.'), array[index].number.end());
			check_stepen_of_per(array[index].per);
			index++;
			i = -1;
			point_mult_del_1.clear();
			answer = 0;
		}
	}
	if (math.size() == 0) plus_minus_per(array);
}
void per_check(string& math, vector<Data>& array)
{
	int index = 0, start, end, index2;
	int kov_sk_40_l = 0, kol_sk_41_l = 0, kol_sk_40_p = 0, kol_sk_41_p = 0;
	bool check = false, check_mult_del = false;
	string point_obr, point;
	for (int i = 0; i < math.size(); i++)
	{
		if ((math[i] > '@' && math[i] < '[') || (math[i] > '`' && math[i] < '{'))
		{
			while ((math[i + 1] > '@' && math[i + 1] < '[') || (math[i + 1] > '`' && math[i + 1] < '{'))
			{
				i++;
			}
			end = i + 1;
			while (true)
			{
				point_obr += math[i];
				i--;
				if (i == -1)
				{
					i = 0;
					break;
				}
				if ((math[i] == '+' || math[i] == '-' || math[i] == '*' || math[i] == '/') && (check_mult_del == false))
				{
					point_obr += math[i];
					break;
				}
			}
			start = i;
			razvorot_chisla(point_obr, point);
			array.push_back(Data());
			for (int i = start; i < end; i++)
			{
				if (math[i] == '+' || math[i] == '-' || math[i] == '*' || math[i] == '/')
				{
					array[index].znak = math[i];
					i++;
				}
				while ((math[i] >= '0' && math[i] <= '9') || math[i] == '.')
				{
					array[index].number += math[i];
					i++;
				}
				while ((math[i] > '@' && math[i] < '[') || (math[i] > '`' && math[i] < '{'))
				{
					array[index].per += math[i];
					i++;
				}
			}
			if (array[index].znak != "+" && array[index].znak != "-" && array[index].znak != "*" && array[index].znak != "/")
			{
				array[index].znak = "+";
			}
			point_obr.clear();
			point.clear();
			transform(array[index].per.begin(), array[index].per.end(), array[index].per.begin(), tolower);
			if (array[index].number.empty()) array[index].number = "1";
			math.erase(math.begin() + start, math.begin() + end);
			check_stepen_of_per(array[index].per);
			index++;
			i = -1;
			check = true;
		}
	}
	if (check == true) plus_minus_per(array);
}
void result_with_per(vector<Data>& array, string& str, bool zero_answer = false)
{
	if (zero_answer == true && array[0].znak == "+") array[0].znak.clear();
	for (int i = 0; i < array.size(); i++)
	{
		cout << array[i].znak;
		str += array[i].znak;

		if (array[i].number != "1" && array[i].number != "0")
		{
			cout << array[i].number;
			str += array[i].number;
		}
		if (array[i].number != "0")
		{
			cout << array[i].per;
			str += array[i].per;
		}
	}
	cout << endl;
}
void mult_vstavka(string& math)
{
	for (int i = 0; i < math.size(); i++)
	{
		if (((i != math.size() && math[i] >= '0' && math[i] <= '9') && ((math[i + 1] > '@' && math[i + 1] < '[') || (math[i + 1] > '`' && math[i + 1] < '{'))) || (((math[i] > '@' && math[i] < '[') || (math[i] > '`' && math[i] < '{')) && ((math[i + 1] > '@' && math[i + 1] < '[') || (math[i + 1] > '`' && math[i + 1] < '{'))))
		{
			math.insert(i + 1, "*");
		}
	}
}
int main()
{
	int menu = 1;
	do
	{
		system("cls");
		SetConsoleOutputCP(1251);
		string math, per, str;
		vector<Data> array;
		unordered_map<char, double> podstanovka;
		double answer = 0;
		bool correct = false;
		cout << "Добро пожаловать в калькулятор!" << endl;
		cout << "Введите математическую задачу: ";
		getline(cin, math);
		math.erase(remove(begin(math), end(math), ' '), end(math));
		while (correct == false)
		{
			correct = true;
			while (!check(math))
			{
				cout << "Повторите ввод: ";
				getline(cin, math);
				math.erase(remove(begin(math), end(math), ' '), end(math));
			}
			mult_delete(math);
			mult_del_check(math, array);
			per_check(math, array);
			skobki_correct(math);
			process_mult_div(math);
			if (!check2(math))
			{
				getline(cin, math);
				correct = false;
			}
		}
		process_plus_minus(math, answer);
		if (answer != 0) str += to_string(answer);
		cout << "Результат вычислений: ";
		if (answer != 0 || array.size() == 0)
		{
			cout << answer;
			result_with_per(array, str);
		}
		else result_with_per(array, str, true);
		answer = 0;
		for (auto el : str)
		{
			if ((el > '@' && el < '[') || (el > '`' && el < '{'))
			{
				podstanovka.emplace(el, 0);
			}
		}
		if (podstanovka.empty())
		{
			cout << "1 - выполнить программу повторно" << endl;
			cout << "0 - завершить работу программы" << endl;
			cout << "Введите ваш выбор: ";
			menu = read_int();
			while (menu < 0 || menu > 1)
			{
				cout << "Указанного вами пункта нет в меню. Введите выбор снова: ";
				menu = read_int();
			}
		}
		else
		{
			cout << "1 - выполнить программу повторно" << endl;
			cout << "2 - подставить значения в переменные" << endl;
			cout << "0 - завершить работу программы" << endl;
			cout << "Введите ваш выбор: ";
			menu = read_int();
			while (menu < 0 || menu > 2)
			{
				cout << "Указанного вами пункта нет в меню. Введите выбор снова: ";
				menu = read_int();
			}
			if (menu == 2)
			{
				for (auto& el : podstanovka)
				{
					cout << "Введите значение переменной " << el.first << ": ";
					el.second = control_per<double>(true, true);
				}
				mult_vstavka(str);
				for (auto el : podstanovka)
				{
					for (int j = 0; j < str.size(); j++)
					{
						if (str[j] == el.first)
						{
							str.erase(j, 1);
							str.insert(j, to_string(el.second));
						}
					}
				}
				while (!check(str))
				{
					cout << "Вы задали некорректные значения. Задайте их повторно: " << endl;
					for (auto el : podstanovka)
					{
						cout << "Введите значение переменной " << el.first << ": ";
						el.second = control_per<double>(true, true);
					}
				}
				skobki_correct(str);
				process_mult_div(str);
				if (!check2(str))
				{
					cout << "Вы задали некорректные значения. Задайте их повторно: " << endl;
					for (auto el : podstanovka)
					{
						cout << "Введите значение переменной " << el.first << ": ";
						el.second = control_per<double>(true, true);
					}
				}

				process_plus_minus(str, answer);
				cout << "Результат вычислений: " << answer << endl;
				cout << "1 - выполнить программу повторно" << endl;
				cout << "0 - завершить работу программы" << endl;
				cout << "Введите ваш выбор: ";
				menu = read_int();
				while (menu < 0 || menu > 1)
				{
					cout << "Указанного вами пункта нет в меню. Введите выбор снова: ";
					menu = read_int();
				}
			}
		}
	} while (menu != 0);
	while (cin.get() != '\n') {};
}
