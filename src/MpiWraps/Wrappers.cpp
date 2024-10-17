/**
 * @file Wrappers.cpp
 * @author DrkWithT
 * @brief Implements MPI type & utility Wrappers.
 * @date 2024-10-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <algorithm>
#include "MpiWraps/Wrappers.hpp"
#include "mpi.h"

namespace MPIRectRule::MpiWraps {
    MPIContext::MPIContext()
    : m_comm_ptr {MPI_COMM_WORLD }, m_comm_size {0}, m_comm_rank {0} {
        MPI_Init(nullptr,nullptr);
        MPI_Comm_size(m_comm_ptr, &m_comm_size);
        MPI_Comm_rank(m_comm_ptr, &m_comm_rank);
    }

    MPI_Comm MPIContext::getCommunicator() { return m_comm_ptr; }

    int MPIContext::getProcessCount() const { return m_comm_size; }

    int MPIContext::getProcessRank() const { return m_comm_rank; }

    MPIContext::~MPIContext() noexcept {
        MPI_Finalize();
    }
}