#ifndef MSPMATRIX_H
#define MSPMATRIX_H

#include <QDebug>
#include <QList>

template<typename T>
class MatrixRow
{
public:
    MatrixRow(int entries)
    {
        int i = 0;
        while(i < entries)
        {
            m_entries.append(reinterpret_cast<T>(0));
            i++;
        }
    }

    //OPERATORS
    const T& operator[](int j) const {return m_entries[j];}
    T& operator[](int j) {return m_entries[j];}

private:
    QList<T> m_entries;
};

template<typename T>
class Matrix
{
public:
    Matrix(int rows, int cols) :
        m_cols(cols),
        m_rows(rows)
    {
        int i = 0;
        while(i < rows)
        {
            m_firstCol.append(cols);
            i++;
        }
    }
    Matrix(QList<QList<T>> multiList) :
        m_cols(multiList.size()),
        m_rows(multiList[0].size())
    {
        int i = 0;
        while(i < multiList[0].size())
        {
            m_firstCol.append(multiList.size());
            i++;
        }
        for(int i = 0; i < m_rows; i++)
        {
            for(int j = 0; j < m_cols; j++)
            {
                m_firstCol[i][j] = multiList[j][i];
            }
        }
    }
    int columns() const {return m_cols;}
    int rows() const {return m_rows;}
    Matrix<T> transponed()
    {
        Matrix<T> m(m_cols, m_rows);
        for(int i = 0; i < m_rows; i++)
        {
            for(int j = 0; j < m_cols; j++)
            {
                m[j][i] = m_firstCol[i][j];
            }
        }
        return m;
    }
    void transpone()
    {
        Matrix<T> m(transponed());
        *this = m;
    }

    //OPERATORS
    Matrix<T> operator+(const Matrix<T>& other)
    {
        Matrix<T> m(m_rows, m_cols);
        if(!(m_rows == other.rows() && m_cols == other.columns())) return m;
        for(int i = 0; i < m_rows; i++)
        {
            for(int j = 0; j < m_cols; j++)
            {
                m[i][j] = m_firstCol[i][j] + other[i][j];
            }
        }
        return m;
    }
    Matrix<T> operator-(const Matrix<T>& other)
    {
        Matrix<T> m(m_rows, m_cols);
        if(!(m_rows == other.rows() && m_cols == other.columns())) return m;
        for(int i = 0; i < m_rows; i++)
        {
            for(int j = 0; j < m_cols; j++)
            {
                m[i][j] = m_firstCol[i][j] - other[i][j];
            }
        }
        return m;
    }
    Matrix<T> operator*(const Matrix<T>& other)
    {
        Matrix<T> m(m_rows, m_rows);
        if(!m_cols == other.rows()) return m;
        T sum = reinterpret_cast<T>(0);
        for(int i = 0; i < m_rows; i++)
        {
            for(int j = 0; j < m_rows; j++)
            {
                for(int k = 0; k < m_cols; k++)
                {
                    sum += m_firstCol[i][k] * other[k][j];
                }
                m[i][j] = sum;
                sum = reinterpret_cast<T>(0);
            }
        }
        return m;
    }
    Matrix<T> operator*(T s) const
    {
        Matrix<T> m(m_rows, m_cols);
        for(int i = 0; i < m_rows; i++)
        {
            for(int j = 0; j < m_cols; j++)
            {
                m[i][j] = s * m_firstCol[i][j];
            }
        }
        return m;
    }
    Matrix<T> operator^(int n) const
    {
        Matrix<T> m(*this);
        Matrix<T> temp(*this);
        for(int i = 0; i < n - 1; i++)
        {
            m = m * temp;
        }
        return m;
    }
    const MatrixRow<T>& operator[](int i) const {return m_firstCol[i];}
    MatrixRow<T>& operator[](int i) {return m_firstCol[i];}
    friend Matrix<T> operator*(T s, const Matrix<T>& m)
    {
        return m * s;
    }

private:
    int m_cols;
    int m_rows;
    QList<MatrixRow<T>> m_firstCol;
};

template<typename T> QDebug& operator<<(QDebug dbg, const Matrix<T>& m)
{
    QString str = "***********************************\n";
    for(int i = 0; i < m.rows(); i++)
    {
        str += "[{";
        for(int j = 0; j < m.columns(); j++)
        {
            str += QString::number(m[i][j]);
            (j < m.columns() - 1) ? str += ", " : str += "";
        }
        (i < m.rows() - 1) ? str += "}]\n" : str += "}]";
    }
    return dbg.noquote() << str;
}

template<typename T> extern T det(const Matrix<T>& m)
{
    int r = m.rows();
    int c = m.columns();
    if(r == c)
    {
        if(r == 1 && c == 1) return m[0][0];
        if(r == 2) return m[0][0] * m[1][1] - m[1][0] * m[0][1];
        if(r == 3) return m[0][0] * m[1][1] * m[2][2] + m[0][1] * m[1][2] * m[2][0] +
                          m[0][2] * m[1][0] * m[2][1] - m[0][2] * m[1][1] * m[2][0] -
                          m[0][1] * m[1][0] * m[2][2] - m[0][0] * m[1][2] * m[2][1];

    }
}

#endif // MSPMATRIX_H
