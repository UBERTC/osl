
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                         statement.h                             **
     **-----------------------------------------------------------------**
     **                   First version: 30/04/2008                     **
     **-----------------------------------------------------------------**

 
 *****************************************************************************
 * OpenScop: Structures and formats for polyhedral tools to talk together    *
 *****************************************************************************
 *    ,___,,_,__,,__,,__,,__,,_,__,,_,__,,__,,___,_,__,,_,__,                *
 *    /   / /  //  //  //  // /   / /  //  //   / /  // /  /|,_,             *
 *   /   / /  //  //  //  // /   / /  //  //   / /  // /  / / /\             *
 *  |~~~|~|~~~|~~~|~~~|~~~|~|~~~|~|~~~|~~~|~~~|~|~~~|~|~~~|/_/  \            *
 *  | G |C| P | = | L | P |=| = |C| = | = | = |=| = |=| C |\  \ /\           *
 *  | R |l| o | = | e | l |=| = |a| = | = | = |=| = |=| L | \# \ /\          *
 *  | A |a| l | = | t | u |=| = |n| = | = | = |=| = |=| o | |\# \  \         *
 *  | P |n| l | = | s | t |=| = |d| = | = | = | |   |=| o | | \# \  \        *
 *  | H | | y |   | e | o | | = |l|   |   | = | |   | | G | |  \  \  \       *
 *  | I | |   |   | e |   | |   | |   |   |   | |   | |   | |   \  \  \      *
 *  | T | |   |   | e |   | |   | |   |   |   | |   | |   | |    \  \  \     *
 *  | E | |   |   |   |   | |   | |   |   |   | |   | |   | |     \  \  \    *
 *  | * |*| * | * | * | * |*| * |*| * | * | * |*| * |*| * | /      \* \  \   *
 *  | O |p| e | n | S | c |o| p |-| L | i | b |r| a |r| y |/        \  \ /   *
 *  '---'-'---'---'---'---'-'---'-'---'---'---'-'---'-'---'          '--'    *
 *                                                                           *
 * Copyright (C) 2008 University Paris-Sud and INRIA                         *
 *                                                                           *
 * (3-clause BSD license)                                                    *
 * Redistribution and use in source  and binary forms, with or without       *
 * modification, are permitted provided that the following conditions        *
 * are met:                                                                  *
 *                                                                           *
 * 1. Redistributions of source code must retain the above copyright notice, *
 *    this list of conditions and the following disclaimer.                  *
 * 2. Redistributions in binary form must reproduce the above copyright      *
 *    notice, this list of conditions and the following disclaimer in the    *
 *    documentation and/or other materials provided with the distribution.   *
 * 3. The name of the author may not be used to endorse or promote products  *
 *    derived from this software without specific prior written permission.  *
 *                                                                           *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR      *
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES *
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.   *
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,          *
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT  *
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, *
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY     *
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT       *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF  *
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.         *
 *                                                                           *
 * OpenScop Library, a library to manipulate OpenScop formats and data       *
 * structures. Written by:                                                   *
 * Cedric Bastoul     <Cedric.Bastoul@u-psud.fr> and                         *
 * Louis-Noel Pouchet <Louis-Noel.pouchet@inria.fr>                          *
 *                                                                           *
 *****************************************************************************/


#ifndef SCOPLIB_STATEMENT_H
# define SCOPLIB_STATEMENT_H

# include <stdio.h>
# include <openscop/macros.h>
# include <openscop/matrix.h>

# if defined(__cplusplus)
extern "C"
  {
# endif


/**
 * The scoplib_statement_t structure stores the useful informations of a given
 * statement to process it within a polyhedral framework.
 */
struct scoplib_statement
{
  scoplib_matrix_list_p domain;   /**< Iteration domain of the statement */
  scoplib_matrix_p schedule;      /**< Scheduling function for the statement */
  scoplib_matrix_p read;          /**< Array read access informations */
  scoplib_matrix_p write;         /**< Array write access informations */
  int nb_iterators;               /**< Original depth of the statement */
  char ** iterators;              /**< Array of (nb_iterators) iterator names */
  char * body;                    /**< Original statement body */


  /** Support for non-static code analysis (See Benabderrahmane's
      Research Report #6814). */
  int nb_exit_predicates;
  char ** exit_predicates;	/**< Array of exit predicats of all
				   while loops of the statement  */
  int nb_control_predicates;
  char ** control_predicates;	/**< Array of control predicats of all
				   irregular if of a statement  */


  struct scoplib_statement * next;/**< Next statement in the linked list */
};
typedef struct scoplib_statement   scoplib_statement_t;
typedef struct scoplib_statement * scoplib_statement_p;


/*+****************************************************************************
 *                          Structure display function                        *
 ******************************************************************************/
void             scoplib_statement_print_structure(FILE *, scoplib_statement_p,
						   int);
void             scoplib_statement_print(FILE *, scoplib_statement_p);
void             scoplib_statement_print_dot_scop(FILE *, scoplib_statement_p,
						  int, char **, int, char **);


/******************************************************************************
 *                               Reading function                             *
 ******************************************************************************/
scoplib_statement_p scoplib_statement_read (FILE*, int, char***, int*);


/*+****************************************************************************
 *                    Memory allocation/deallocation function                 *
 ******************************************************************************/
scoplib_statement_p scoplib_statement_malloc();
void                scoplib_statement_free(scoplib_statement_p);


/*+****************************************************************************
 *                            Processing functions                            *
 ******************************************************************************/
void             scoplib_statement_add(scoplib_statement_p *, scoplib_statement_p);
void             scoplib_statement_compact(scoplib_statement_p, int);
int              scoplib_statement_number(scoplib_statement_p);


# if defined(__cplusplus)
  }
# endif
#endif /* define SCOPLIB_STATEMENT_H */
