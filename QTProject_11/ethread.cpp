#include "ethread.h"

EThread::EThread(QString thread_name, size_t ind, MainWindow& MW):
    name(thread_name), index(ind), mw(MW)
{
    this->moveToThread(this);
}

void EThread::Pause(){
    if(index == 1)
        mw.SetPaus(true);

    if(index == 2)
        mw.SetPaus(false);

    mw.SetFLAG_s_Ethread(index, true);
    mw.GetMutex().unlock();
}

void EThread::Resume(){
    if(index == 1){
        while(mw.GetPaus()){
            SuspendThread(this);
        }
    }

    if(index == 2){
        while(!mw.GetPaus()){
            SuspendThread(this);
        }
    }

    mw.GetMutex().lock();
}

void EThread::run()
{
  /*
    switch(index)
    {
    case(1):
            for(size_t j = 0; j < mw.GetORD(); j++)
            {
                //if(j < 2) Resume();

                Resume();

                //qDebug() << "thread 1";
                //qDebug() << "\033[31m" << j << "\033[0m";

                for(size_t i = 0; i < mw.GetORD(); i++)
                {
                    if(j == 0){
                            mw.GA()[i][j] = mw.setNewValue(mw.GetQElem_s_1()[i][0].qLineEdit->text());

                    }else if(i>=j){

                        auto SUMM = [this, i, j](auto& summ,int start, int end) -> double{

                            if(start > end) return 0;

                            //qDebug() << "\033[31m" << i << " :: " << j;

                            //qDebug() <<"\033[33m" << mw.GU()[i][start] << "\033[0m";//+
                            //qDebug() << "\033[33m" << mw.GC()[start][j] << "\033[0m";//-

                            return mw.GA()[i][start]* mw.GB()[start][j] + summ(summ,start + 1, end);
                        };

                        //qDebug() << mw.setNewValue(mw.GetQElem_s_1()[i][j].qLineEdit->text());
                        //if(i == 3)
                        //qDebug() << "\033[32m" << SUMM(SUMM,0, j - 1) << "\033[0m";

                       mw.GA()[i][j] = mw.setNewValue(mw.GetQElem_s_1()[i][j].qLineEdit->text()) - SUMM(SUMM,0, j - 1);
                    }
                }
                //if((j == 0) || (j== mw.GetORD() - 1)) Pause();

                Pause();
             }
        break;
    case(2):
        for(size_t i = 0; i < mw.GetORD(); i++)
        {
            //if(i < 2) Resume();

            Resume();

            //qDebug() << "thread 2";
            //qDebug() << "\033[32m" << i << "\033[0m";

            for(size_t j = 0; j < mw.GetORD(); j++){
                if(i == j){
                    mw.GB()[i][j] = 1;
                }else if(j>i){
                    auto SUMM = [this, i, j](auto& summ,int start, int end) -> double{

                        if(start > end) return 0;

                        return mw.GA()[i][start]* mw.GB()[start][j] + summ(summ,start + 1, end);
                    };

                   mw.GB()[i][j] = ((mw.setNewValue(mw.GetQElem_s_1()[i][j].qLineEdit->text()) - SUMM(SUMM,0, j - 1))/(mw.GA()[i][i]));
                }

                if((i == 0) && (j >0)){
                    mw.GA()[i][j] = mw.setNewValue(mw.GetQElem_s_1()[i][j].qLineEdit->text()) / mw.GA()[i][i];
                }
            }
            //if((i == 0) || (i == mw.GetORD() - 1)) Pause();

            Pause();
        }
        break;
    default:
        break;
    };
*/
}
