/*
* MIT License
*
* Copyright (c) 2017 wen.gu <454727014@qq.com>
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#include "neuron_utils.h"

progressDisplay::progressDisplay(int maxValue)
	:mMaxValue(maxValue),
	mNumStarPer10Percent(5),
	mProgValue(0),
	mMaxStarCnt(50),
	mCurStarCnt(0)
{
	cout << "0%";
	for (size_t i = 1; i < 10; i++)
	{
		int progValue = i * 10;
		cout << setfill(' ') << setw(mNumStarPer10Percent) << progValue;

		if (i == 9)
		{
			/** 100%  and 50 mush than 2 char, so we need + 2 */
			cout << setfill(' ') << setw(mNumStarPer10Percent + 2) << "100%" << endl;
		}
	}

	for (size_t i = 0; i < 10; i++)
	{
		cout << '|' << setfill('-') << setw(mNumStarPer10Percent);
	}
	cout << '|' << endl;
}

progressDisplay::~progressDisplay()
{
	cout << endl;
}

progressDisplay& progressDisplay::operator++()
{
	updateProgress(mProgValue + 1);

	return *this;
}

progressDisplay& progressDisplay::operator++(int)
{
	updateProgress(mProgValue + 1);

	return *this;
}

void progressDisplay::updateProgress(int progressValue)
{
	mProgValue = progressValue;
	int progValue = mProgValue * mMaxStarCnt / mMaxValue;

	if (progValue > mCurStarCnt)
	{
		cout <<'\r' << setfill(PROGRESS_DISP_CHAR) << setw(progValue) << PROGRESS_DISP_CHAR;
		mCurStarCnt = progValue;

		if (mCurStarCnt >= mMaxStarCnt)
		{
			cout << PROGRESS_DISP_CHAR << endl;
		}
	}
}
