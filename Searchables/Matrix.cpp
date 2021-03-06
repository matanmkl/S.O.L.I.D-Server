//
// Created by sapir on 14/01/2020.
//

#include "Matrix.h"

Matrix::Matrix(vector<vector<double>> matrix, State<Position> *init, State<Position> *goal) {
    this->matrix = matrix;
    this->init = init;
    this->goal = goal;
}

State<Position> *Matrix::getInitialState() {
    return this->init;
}

State<Position> *Matrix::getGoalState() {
    return this->goal;
}

bool Matrix::isGoalState(State<Position> *state) {
    return (*state == *this->goal);
}

double Matrix::calcHeuristic(State<Position> *current) {
    int iCurrent = current->getState().getRow();
    int jCurrent = current->getState().getCol();
    int iGoal = this->goal->getState().getRow();
    int jGoal = this->goal->getState().getCol();
    // heuristic function
    double f = abs(iCurrent - iGoal) + abs(jCurrent - jGoal);
    return f;
}

vector<State<Position> *> Matrix::getAllPossibleStates(State<Position> *state) {
    Position pos = state->getState();
    int i, j;
    i = pos.getRow();
    j = pos.getCol();
    vector<State<Position> *> adj;
    //up
    if (this->isInBoundaries(i - 1, j)) {
        State<Position> *s = new State<Position>(Position(i - 1, j), this->matrix[i - 1][j],
                                                 this->matrix[i - 1][j] + state->getTrialCost(), state, "Up");
        adj.push_back(s);
    }
    //down
    if (this->isInBoundaries(i + 1, j)) {
        adj.push_back(new State<Position>(Position(i + 1, j), this->matrix[i + 1][j],
                                          this->matrix[i + 1][j] + state->getTrialCost(), state, "Down"));
    }
    //left
    if (this->isInBoundaries(i, j - 1)) {
        adj.push_back(new State<Position>(Position(i, j - 1), this->matrix[i][j - 1],
                                          this->matrix[i][j - 1] + state->getTrialCost(), state, "Left"));
    }
    //right
    if (this->isInBoundaries(i, j + 1)) {
        adj.push_back(new State<Position>(Position(i, j + 1), this->matrix[i][j + 1],
                                          this->matrix[i][j + 1] + state->getTrialCost(), state, "Right"));
    }
    return adj;
}

bool Matrix::isInBoundaries(int row, int col) {
    if ((0 <= row && row <= this->matrix.size() - 1) && (0 <= col && col <= this->matrix[0].size() - 1)) {
        if (this->matrix[row][col] != INFINITY) {
            return true;
        }
    }
    return false;
}

string Matrix::toString() {
    string matrixStr;
    for (vector<double> vec:this->matrix) {
        for (double value:vec) {
            matrixStr.append(to_string(value));
            matrixStr.append(DELIMITER);
        }
        matrixStr.append("\n");
    }
    matrixStr.append("\n");
    matrixStr.append(this->init->getState().toString());
    matrixStr.append("\n");
    matrixStr.append(this->goal->getState().toString());
    matrixStr.append("\n");
    return matrixStr;

}


