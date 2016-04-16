#ifndef SUDOKUSOLVER_CORE_BOARD_HPP_INCLUDED
#define SUDOKUSOLVER_CORE_BOARD_HPP_INCLUDED

#include <sudokusolver/cell.hpp>

#include <array>

namespace SudokuSolver {  namespace Core
{

class Board
{
public:
    static const unsigned int SIZE = Cell::VALUE_COUNT - 1; //-1 because of VALUE_UNSET

    //TODO: const_iterator
    class iterator : public std::iterator<std::bidirectional_iterator_tag, Cell*>
    {
    public:
        iterator(Board& board, int xPosition = 0, int yPosition = 0);
        iterator(const iterator& rhs);
        virtual ~iterator();
        iterator& operator=(const iterator& rhs);
        iterator& operator++();
        iterator& operator--();
        iterator operator++(int);
        iterator operator--(int);
        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;
        Cell& operator->() const;
        Cell& operator*() const;

        int xPosition() const;
        int yPosition() const;

    private:
        Board& m_board;
        int m_xPosition;
        int m_yPosition;
    };
private:
    typedef std::array<std::array<Cell,Cell::VALUE_COUNT>,Cell::VALUE_COUNT> CellArray;
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
private:
    CellArray m_cells;
};

}}

#endif //SUDOKUSOLVER_CORE_BOARD_HPP_INCLUDED
