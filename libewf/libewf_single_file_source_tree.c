/*
 * Single file source tree functions
 */

#include <common.h>
#include <types.h>

#include "libewf_libcdata.h"
#include "libewf_libcerror.h"
#include "libewf_libuna.h"
#include "libewf_single_file_source.h"
#include "libewf_single_file_source_tree.h"

/* Retrieves the single file source sub node for the specific source id
 * Returns 1 if successful, 0 if no such sub single file source or -1 on error
 */
int libewf_single_file_source_tree_get_sub_node_by_id(
	libcdata_tree_node_t *node,
	uint32_t source_id,
	libcdata_tree_node_t **sub_node,
	libewf_single_file_source_t **sub_single_file_source,
	libcerror_error_t **error)
{
	static char *function   = "libewf_single_file_source_tree_get_sub_node_by_id";
	int number_of_sub_nodes = 0;
	int sub_node_index      = 0;

	if( node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid node.",
		 function );

		return( -1 );
	}
	if( sub_node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sub node.",
		 function );

		return( -1 );
	}
	if( sub_single_file_source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sub single file source.",
		 function );

		return( -1 );
	}
	if( libcdata_tree_node_get_number_of_sub_nodes(
	     node,
	     &number_of_sub_nodes,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of sub nodes.",
		 function );

		goto on_error;
	}
	if( libcdata_tree_node_get_sub_node_by_index(
	     node,
	     0,
	     sub_node,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve first sub node.",
		 function );

		goto on_error;
	}
	for( sub_node_index = 0;
	     sub_node_index < number_of_sub_nodes;
	     sub_node_index++ )
	{
		if( libcdata_tree_node_get_value(
		     *sub_node,
		     (intptr_t **) sub_single_file_source,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve value from sub node: %d.",
			 function,
			 sub_node_index );

			goto on_error;
		}
		if( *sub_single_file_source == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing sub single file source: %d.",
			 function,
			 sub_node_index );

			goto on_error;
		}
		if ((*sub_single_file_source)->id == source_id)
		{
			break;
		}
		if( libcdata_tree_node_get_next_node(
		     *sub_node,
		     sub_node,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve next node from sub node: %d.",
			 function,
			 sub_node_index );

			goto on_error;
		}
	}
	if( sub_node_index >= number_of_sub_nodes )
	{
		*sub_node               = NULL;
		*sub_single_file_source = NULL;

		return( 0 );
	}
	return( 1 );

on_error:
	*sub_node               = NULL;
	*sub_single_file_source = NULL;

	return( -1 );
}