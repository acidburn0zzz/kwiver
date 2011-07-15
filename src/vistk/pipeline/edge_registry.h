/*ckwg +5
 * Copyright 2011 by Kitware, Inc. All Rights Reserved. Please refer to
 * KITWARE_LICENSE.TXT for licensing information, or contact General Counsel,
 * Kitware, Inc., 28 Corporate Drive, Clifton Park, NY 12065.
 */

#ifndef VISTK_PIPELINE_EDGE_REGISTRY_H
#define VISTK_PIPELINE_EDGE_REGISTRY_H

#include "types.h"

#include <boost/function.hpp>

#include <string>
#include <map>
#include <vector>

namespace vistk
{

/// A function which returns an \ref edge.
typedef boost::function<edge_t (config_t const& config)> edge_ctor_t;

/**
 * \class edge_registry
 *
 * \brief A registry of edges which can generate edges of a different types.
 *
 * \ingroup registries
 */
class edge_registry
{
  public:
    /// The type of registry keys.
    typedef std::string type_t;
    /// A group of types.
    typedef std::vector<type_t> types_t;

    /**
     * \brief Destructor.
     */
    ~edge_registry();

    /**
     * \brief Adds an edge type to the registry.
     *
     * \throws edge_type_already_exists Thrown if the type already exists.
     *
     * \param type The name of the \ref edge type.
     * \param ctor The function which creates the edge of the \p type.
     */
    void register_edge(type_t const& type, edge_ctor_t ctor);
    /**
     * \brief Creates an edge of a specific type.
     *
     * \throws no_such_edge_type Thrown if the type is not known.
     *
     * \param type The name of the type of \ref edge to create.
     * \param config The configuration to pass the \ref edge.
     */
    edge_t create_edge(type_t const& type, config_t const& config);

    /**
     * \brief Returns all of the known types.
     */
    types_t types() const;

    /**
     * \brief Returns a pointer to the registry to use.
     */
    static edge_registry_t self();

    /// The default edge implementation to use.
    static type_t const default_type;
  private:
    edge_registry();

    static edge_registry_t m_self;

    typedef std::map<type_t, edge_ctor_t> edge_store_t;
    edge_store_t m_registry;
};

} // end namespace vistk

#endif // VISTK_PIPELINE_EDGE_REGISTRY_H
