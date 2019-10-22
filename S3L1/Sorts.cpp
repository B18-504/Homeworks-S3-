#pragma once

template <typename T>
void QuickSort(Sequence<T> &seq, char comparison(T &a, T &b))
{
    if(seq.GetLen() > 1)
    {
        CallStack<T> CS = CallStack<T>();
        typename Sequence<T>::Slider *sllold = &seq.InitSlider(0), *slrold = &seq.InitSlider(seq.GetLen()-1);
        typename Sequence<T>::Slider *sll, *slr;
        Call<T> *buff;
        char call_condition = -1;
        bool r_swap, l_swap;
        push_start(CS);

        while(call_condition != 2)
        {
            l_swap = 0;
            r_swap = 0;
            sll = &(sllold->Clone());
            slr = &(slrold->Clone());
            slr->ShiftLeft();


            while(sll->GetPosition() < slr->GetPosition())
            {
                if(!l_swap)
                {
                    if(comparison(*(sll->GetVal()), *(slrold->GetVal())))
                    {
                        sll->ShiftRight();
                    }
                    else
                    {
                        l_swap = 1;
                    }
                }
                if(!r_swap)
                {
                    if(comparison(*(slrold->GetVal()), *(slr->GetVal())))
                    {
                        slr->ShiftLeft();
                    }
                    else
                    {
                        r_swap = 1;
                    }
                }

                if(r_swap * l_swap)
                {
                    l_swap = 0;
                    r_swap = 0;
                    swap<T>(*sll, *slr);

                    sll->ShiftRight();
                    slr->ShiftLeft();
                }
            }

            if(sll->GetPosition() > slr->GetPosition())
            {
                slr->ShiftRight();
                sll->ShiftLeft();
                swap<T>(*slr, *slrold);
            }
            else if(comparison(*(slrold->GetVal()), *(slr->GetVal())))
            {
                swap<T>(*slr, *slrold);
                slr->ShiftRight();
            }
            else
            {
                slr->ShiftRight();
                swap<T>(*slr, *slrold);
            }

            if(slrold->GetPosition() != slr->GetPosition())
            {
                push(CS, slr, slrold);
            }
            else
            {
                push_shift(CS);
                delete slr;
                delete slrold;
            }

            if(sllold->GetPosition() != sll->GetPosition())
            {
                slrold = sll;
            }
            else 
            {
                delete sll;
                delete sllold;
                do
                {
                    pop<T>(CS, buff);
                    call_condition = buff->cond;
                    if(call_condition == 0)
                    {
                        sllold = buff->left;
                        slrold = buff->right;
                    }
                    free(buff);
                } while(call_condition == 1);
            }
        }
    }
}

template <typename T>
void InsertSort(Sequence<T> &seq, char comparison(T &a, T &b))
{
    if(seq.GetLen() > 1)
    {
        typename Sequence<T>::Slider *border = &seq.InitSlider(1), *slr, *sll;
        T *buff;
        
        try
        {
			//(until OoR)
N:          slr = &(border->Clone());								//Ждём OoR
            sll = &(border->Clone());
            sll->ShiftLeft();
            
            buff = border->GetVal();

            try
            {
				//(until OoR or found)
M:              if(!comparison(*(sll->GetVal()), *buff))            //Вечный цикл, выход при обнаружении нужного элемента или левого конца
                {
                    slr->SetVal(sll->GetVal());
                    sll->ShiftLeft();
                    slr->ShiftLeft();
                    goto M;
                }
                else
                {
                    slr->SetVal(buff);
                }
            }
            catch(Exception E)
            {
				delete slr, sll;
                if(E.code != 0x12)
                {
                    throw E;
                }
                sll->SetVal(buff);
            }

            border->ShiftRight();
            goto N;
        }
        catch(Exception E)
        {
			delete border;
            if(E.code != 0x12)
            {
                throw E;
            }
        }
    }
}
