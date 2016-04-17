#ifndef SUDOKUSOLVER_CORE_BOARD_HPP_INCLUDED
#define SUDOKUSOLVER_CORE_BOARD_HPP_INCLUDED

#include <sudokusolver/cell.hpp>

#include <array>
#include <string>

namespace SudokuSolver {  namespace Core
{

class Board
{
public:
    static const unsigned int SIZE = Cell::VALUE_COUNT - 1; //-1 because of VALUE_UNSET

    //TODO: const_iterator, but not needed right now... nice to have
    class iterator : public std::iterator<std::bidirectional_iterator_tag, Cell*>
    {
    public:
        iterator(Board& board, int xPosition = 0, int yPosition = 0);
        iterator(const iterator& rhs);
        virtual ~iterator();

        //TODO: operators as friend functions where applicable
        iterator& operator=(const iterator& rhs);
        virtual iterator& operator++();
        virtual iterator& operator--();
        iterator operator++(int);
        iterator operator--(int);
        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;
        Cell* operator->() const;
        Cell& operator*() const;
        //FIXME: missing operators commented below
        //iterator operator+(int offset);
        //iterator operator-(int offset);
        //iterator& operator+=(int offset);
        //iterator& operator-=(int offset);
        //sizeof-operator
        //bool operator<(const iterator& rhs) const;
        //bool operator<=(const iterator& rhs) const;
        //bool operator>(const iterator& rhs) const;
        //bool operator>=(const iterator& rhs) const;

        int xPosition() const;
        int yPosition() const;

    protected:
        Board& m_board;
        int m_xPosition;
        int m_yPosition;
    };

    class editable_iterator : public iterator {
    public:
        editable_iterator(const iterator& iterator);
        virtual ~editable_iterator();
        editable_iterator& operator++();
        editable_iterator& operator--();
    };

    class vertical_iterator : public iterator {
    public:
        vertical_iterator(const iterator& iterator);
        virtual ~vertical_iterator();
        vertical_iterator& operator++();
        vertical_iterator& operator--();
    };

    class diagonal_iterator : public iterator {
    public:
        diagonal_iterator(const iterator& iterator);
        virtual ~diagonal_iterator();
        diagonal_iterator& operator++();
        diagonal_iterator& operator--();
    };

    class Parser {
    public:
        static Board fromStdString(const std::string& boardStr);
        static std::string toStdString(const Board& board);
    };

public:
    class Exception : public std::exception
    {
        // exception interface
    public:
        virtual const char* what() const throw ();
        const Board& board() const;

    protected:
        Exception(const Board& board);
        Exception(const Exception& rhs);
        virtual ~Exception();
        Exception& operator=(const Exception& rhs);
    protected:
        const Board* m_board;
        std::string m_message;
    };

    class IllegalOperationException : public Exception
    {
    public:
        explicit IllegalOperationException(const Board& board, const std::string& operation);
        virtual ~IllegalOperationException();
    private:
        std::string m_operation;
    };
private:
    typedef std::array<std::array<Cell,Board::SIZE>,Board::SIZE> CellArray;
public:
    Board();
    Board(const Board& rhs);
    virtual ~Board();
    Board& operator=(const Board& rhs);
public:
    Cell& cell(unsigned int xPosition, unsigned int yPosition);

    Board::iterator begin();
    Board::iterator end();
    Board::iterator rbegin();
    Board::iterator rend();

    Board::iterator begin_row(unsigned int row);
    Board::iterator end_row(unsigned int row);
    Board::iterator rbegin_row(unsigned int row);
    Board::iterator rend_row(unsigned int row);

    Board::iterator begin_column(unsigned int column);
    Board::iterator end_column(unsigned int column);
    Board::iterator rbegin_column(unsigned int column);
    Board::iterator rend_column(unsigned int column);

private:
    CellArray m_cells;
};

}}

#endif //SUDOKUSOLVER_CORE_BOARD_HPP_INCLUDED
