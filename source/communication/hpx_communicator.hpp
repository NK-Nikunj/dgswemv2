#ifndef HPX_COMMUNICATOR_HPP
#define HPX_COMMUNICATOR_HPP

#include <hpx/hpx.hpp>
#include <hpx/include/iostreams.hpp>

#include "general_definitions.hpp"
#include "preprocessor/mesh_metadata.hpp"

using array_double = std::vector<double>;
HPX_REGISTER_CHANNEL_DECLARATION(array_double);

struct HPXRankBoundary {
    RankBoundaryMetaData db_data;

    hpx::lcos::channel<array_double> outgoing;
    hpx::lcos::channel<array_double> incoming;

    std::vector<double> send_preproc_buffer;
    std::vector<double> receive_preproc_buffer;

    std::vector<double> send_buffer;
    std::vector<double> receive_buffer;

    std::vector<double> send_postproc_buffer;
    std::vector<double> receive_postproc_buffer;

    template <typename Archive>
    void serialize(Archive& ar, unsigned) {
        // clang-format off
        ar  & db_data
            & outgoing
            & incoming
            & send_preproc_buffer  // probably unnecessary (can be optimized later)
            & receive_preproc_buffer
            & send_buffer
            & receive_buffer
            & send_postproc_buffer
            & receive_postproc_buffer;
        // clang-format on
    }
};

class HPXCommunicator {
  private:
    std::vector<HPXRankBoundary> rank_boundaries;

  public:
    HPXCommunicator() = default;
    HPXCommunicator(const DistributedBoundaryMetaData& db_data);

    uint GetRankBoundaryNumber() { return this->rank_boundaries.size(); }
    HPXRankBoundary& GetRankBoundary(uint rank_boundary_id) { return this->rank_boundaries.at(rank_boundary_id); }

    void SendPreprocAll(const uint timestamp);
    hpx::future<void> ReceivePreprocAll(const uint timestamp);

    void SendAll(const uint timestamp);
    hpx::future<void> ReceiveAll(const uint timestamp);

    void SendPostprocAll(const uint timestamp);
    hpx::future<void> ReceivePostprocAll(const uint timestamp);

  public:
    using RankBoundaryType = HPXRankBoundary;

    template <typename Archive>
    void serialize(Archive& ar, unsigned) {
        // clang-format off
        ar  & rank_boundaries;
        // clang-format on
    }
};

#endif
