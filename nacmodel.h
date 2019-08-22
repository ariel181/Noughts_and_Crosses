#ifndef NACMODEL_H
#define NACMODEL_H

#include <QObject>
#include <QVector>
#include "item.h"
/*!
 * \class NACModel
 * \brief The NACModel class  Represented logic for crosses and noughts.
 */

class NACModel : public QObject
{
    Q_OBJECT
public:

    explicit NACModel(QObject *parent = nullptr);

signals:
    /*!
     * \brief Emitted when user win.
     */
    void NotifyUserWin();
    /*!
     * \brief Emitted when players not have move.
     */
    void NotifyUserDraw();

public slots:
    /*!
     * \brief Saves the current move and checks if the user has won or is tied
     *
     * \param index
     * \param item
     */
    void userMove(int index, Item item);

private:
    /*!
     * \fn bool NACModel::isWin(Item item)
     * \brief Method check is user win.
     *
     * \param item
     * \return bool
     */
    bool isWin(Item item);
    /*!
     * \fn bool NACModel::isDraw(Item item)
     * \brief Method check is players have draw.

     * \return bool
     */
    bool isDraw();

    QVector<Item> _board;

};

#endif // NACMODEL_H
