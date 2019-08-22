#include "nacmodel.h"
#include <QDebug>

NACModel::NACModel(QObject *parent) : QObject(parent)
  ,_board(10,Item::Non)
{


}

void NACModel::userMove(int index, Item item)
{

    if(index > _board.size()) return;

    _board[index] = item;

    if(isWin(item)) {
        _board = {10,Item::Non};
        emit NotifyUserWin();
        return ;
    }

    if(isDraw()) {
        _board = {10,Item::Non};
        emit NotifyUserDraw();
        return ;
    }


}

bool NACModel::isWin(Item item)
{
    auto g = item;

    bool line = false;

    for(int i = 0; i <= 6; i += 3) line |= ((_board[i] == g) && (_board[i+1] == g) && (_board[i+2] == g));

    for(int i = 0; i <= 2; i++)    line |= ((_board[i] == g) && (_board[i+3] == g) && (_board[i+6] == g));

    line |= ((_board[0] == g) && (_board[4] == g) && (_board[8] == g));

    line |= ((_board[2] == g) && (_board[4] == g) && (_board[6] == g));

    return line;

}

bool NACModel::isDraw()
{
    for(int i = 0; i < 9; i++) if(_board[i] == Item::Non) return false;
    return true;
}
