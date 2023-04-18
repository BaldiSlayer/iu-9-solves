package main

import (
    "fmt"
)

// Helper function to print a matrix
func printMatrix(matrix [][]float64) {
    for i := 0; i < len(matrix); i++ {
        for j := 0; j < len(matrix[i]); j++ {
            fmt.Printf("%6.2f ", matrix[i][j])
        }
        fmt.Println()
    }
    fmt.Println()
}

// Helper function to swap two rows in a matrix
func swapRows(matrix [][]float64, row1, row2 int) {
    temp := matrix[row1]
    matrix[row1] = matrix[row2]
    matrix[row2] = temp
}

// Helper function to perform row reduction on a matrix
func rowReduce(matrix [][]float64) {
    numRows := len(matrix)
    numCols := len(matrix[0])

    // Perform Gaussian elimination on the matrix
    for i := 0; i < numRows; i++ {
        // Find the row with the largest absolute value in the current column
        maxIndex := i
        for j := i + 1; j < numRows; j++ {
            if matrix[j][i] > matrix[maxIndex][i] {
                maxIndex = j
            }
        }

        // Swap the current row with the row containing the largest absolute value
        if maxIndex != i {
            swapRows(matrix, i, maxIndex)
        }

        // Normalize the current row
        pivot := matrix[i][i]
        for j := i; j < numCols; j++ {
            matrix[i][j] /= pivot
        }

        // Eliminate all other entries in the current column
        for j := 0; j < numRows; j++ {
            if j != i {
                factor := matrix[j][i]
                for k := i; k < numCols; k++ {
                    matrix[j][k] -= factor * matrix[i][k]
                }
            }
        }
    }
}

// Main function to solve a system of linear equations using the Gaussian elimination method
func main() {
    // Define the system of equations as a matrix
    matrix := [][]float64{{1, 2, 3, 7},
                          {4, 5, 6, 8},
                          {7, 8, 9, 9}}

    // Print the matrix before row reduction
    fmt.Println("Matrix before row reduction:")
    printMatrix(matrix)

    // Perform row reduction on the matrix
    rowReduce(matrix)

    // Print the matrix after row reduction
    fmt.Println("Matrix after row reduction:")
    printMatrix(matrix)

    // Print the solution to the system of equations
    fmt.Println("Solution:")
    for i := 0; i < len(matrix); i++ {
        fmt.Printf("x%d = %6.2f\n", i+1, matrix[i][len(matrix[i])-1])
    }
}
