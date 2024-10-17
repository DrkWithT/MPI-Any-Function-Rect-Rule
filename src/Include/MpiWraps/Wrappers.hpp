#ifndef WRAPPERS_HPP
#define WRAPPERS_HPP

#include <mpi.h>
#include <cstddef>

#include "Models/FunctionParts.hpp"

namespace MPIRectRule::MpiWraps {
    /**
     * @brief RAII wrapper for basic MPI state.
     * @note Only 1 must be created for the multi-role process code at all times.
     */
    class MPIContext {
    private:
        static constexpr int Master_Rank = 0;

        MPI_Comm m_comm_ptr;
        int m_comm_size;
        int m_comm_rank;

    public:
        explicit MPIContext();

        MPIContext(const MPIContext& other) = delete;
        MPIContext& operator=(const MPIContext& other) = delete;

        [[nodiscard]] constexpr int getMasterRank() const { return Master_Rank; }

        MPI_Comm getCommunicator();
        [[nodiscard]] int getProcessCount() const;
        [[nodiscard]] int getProcessRank() const;

        ~MPIContext() noexcept;
    };
}

#endif