/*ckwg +5
 * Copyright 2012 by Kitware, Inc. All Rights Reserved. Please refer to
 * KITWARE_LICENSE.TXT for licensing information, or contact General Counsel,
 * Kitware, Inc., 28 Corporate Drive, Clifton Park, NY 12065.
 */

#ifndef VISTK_PYTHON_HELPERS_PYTHON_EXCEPTIONS_H
#define VISTK_PYTHON_HELPERS_PYTHON_EXCEPTIONS_H

/// \todo More useful output?

#define HANDLE_PYTHON_EXCEPTION(call)             \
  try                                             \
  {                                               \
    call;                                         \
  }                                               \
  catch (boost::python::error_already_set const&) \
  {                                               \
    python_print_exception();                     \
                                                  \
    throw;                                        \
  }

#define HANDLE_PYTHON_EXCEPTION_IGNORE(call)       \
  try                                              \
  {                                                \
    call;                                          \
  }                                                \
  catch (boost::python::error_already_set const&)  \
  {                                                \
    python_print_exception();                      \
  }

#define TRANSLATE_PYTHON_EXCEPTION(call)           \
  try                                              \
  {                                                \
    call;                                          \
  }                                                \
  catch (std::exception const& e)                  \
  {                                                \
    vistk::python::python_gil const gil;           \
                                                   \
    (void)gil;                                     \
                                                   \
    PyErr_SetString(PyExc_RuntimeError, e.what()); \
                                                   \
    throw;                                         \
  }

void python_print_exception();

#endif // VISTK_PYTHON_HELPERS_PYTHON_EXCEPTIONS_H
