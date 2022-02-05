#include <iostream>
#include <process.h>
#include <Windows.h>
#pragma warning(disable : 5208)


namespace pp_lbwapi
{
	const size_t NTHREAD = 4;
	const size_t COUNT = 100;

	class lbwapi
	{
	public:

		int array[COUNT] = { 1, -2, 4, -6, 7, -8, 3, -4, 5, -6, 7, -5, 5, -8, 3, -2, 7, -4, 9, -1,
		1, -2, 4, -6, 7, -8, 3, -4, 5, -6, 7, -5, 5, -8, 3, -2, 7, -4, 9, -1,
		1, -2, 4, -6, 7, -8, 3, -4, 5, -6, 7, -5, 5, -8, 3, -2, 7, -4, 9, -1,
		1, -2, 4, -6, 7, -8, 3, -4, 5, -6, 7, -5, 5, -8, 3, -2, 7, -4, 9, -1, 
		1, -2, 4, -6, 7, -8, 3, -4, 5, -6, 7, -5, 5, -8, 3, -2, 7, -4, 9, -1 };

		using INFORM = struct {
			int* array;		// Указатель на структуру с которой работаем
			size_t left, right;		// Границы структуры
			bool res = true;		// Результат исследования выбранной части струкуры(результат одного потока)
		};

		static unsigned __stdcall alter_sign(void* arg)
		{
			INFORM* inform = (INFORM*)arg;
			inform->res = true;
			size_t i = inform->left + 1;
			do
			{
				inform->res = inform->array[i - 1] > 0 ? inform->array[i] < 0 : inform->array[i];
				++i;
			} while (i < inform->right && inform->res);
			_endthreadex(0);
			return 0;
		}

		int sign_parallel(int array[])
		{
			HANDLE t[NTHREAD];
			INFORM informs[NTHREAD];
			size_t block_size = COUNT / NTHREAD;

			for (size_t i = 0; i < NTHREAD; ++i)
			{
				informs[i].array = array;
				informs[i].left = block_size * i;
				if (i == NTHREAD - 1)
				{
					informs[i].right = COUNT;
				}
				else
				{
					informs[i].right = block_size * (i + 1) + 1;
				}
				informs[i].res = true;
				t[i] = (HANDLE)_beginthreadex(nullptr, 0, &alter_sign, &informs[i], 0, nullptr);
			}

			WaitForMultipleObjects(NTHREAD, t, true, INFINITE);

			bool global_res = true;
			for (size_t i = 0; i < NTHREAD; ++i)
			{
				global_res = global_res && informs[i].res;
			}

			for (size_t i = 0; i < NTHREAD; ++i)
			{
				CloseHandle(t[i]);
			}

			return global_res;
		}
	};
}