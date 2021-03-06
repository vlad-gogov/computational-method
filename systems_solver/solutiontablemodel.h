#ifndef SOLUTIONTABLEMODEL_H
#define SOLUTIONTABLEMODEL_H

#include <vector>

#include <QAbstractTableModel>
#include <QMessageBox>

#include "matrix.h"
#include "solution.h"

class SolutionTableModel : public QAbstractTableModel
{
    Q_OBJECT

    int m_eq_count;
    std::vector<Solution> m_solutions;

public:
    explicit SolutionTableModel(const std::vector<Solution>& solutions, QObject *parent = nullptr);
    ~SolutionTableModel() = default;

protected:
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int column, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};

#endif // SOLUTIONTABLEMODEL_H
