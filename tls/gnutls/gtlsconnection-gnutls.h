/* GIO - GLib Input, Output and Streaming Library
 *
 * Copyright 2009 Red Hat, Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2 of the licence or (at
 * your option) any later version.
 *
 * See the included COPYING file for more information.
 *
 * In addition, when the library is used with OpenSSL, a special
 * exception applies. Refer to the LICENSE_EXCEPTION file for details.
 */

#ifndef __G_TLS_CONNECTION_GNUTLS_H__
#define __G_TLS_CONNECTION_GNUTLS_H__

#include <gio/gio.h>
#include <gnutls/gnutls.h>

G_BEGIN_DECLS

#define G_TYPE_TLS_CONNECTION_GNUTLS            (g_tls_connection_gnutls_get_type ())
#define G_TLS_CONNECTION_GNUTLS(inst)           (G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_TLS_CONNECTION_GNUTLS, GTlsConnectionGnutls))
#define G_TLS_CONNECTION_GNUTLS_CLASS(class)    (G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_TLS_CONNECTION_GNUTLS, GTlsConnectionGnutlsClass))
#define G_IS_TLS_CONNECTION_GNUTLS(inst)        (G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_TLS_CONNECTION_GNUTLS))
#define G_IS_TLS_CONNECTION_GNUTLS_CLASS(class) (G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_TLS_CONNECTION_GNUTLS))
#define G_TLS_CONNECTION_GNUTLS_GET_CLASS(inst) (G_TYPE_INSTANCE_GET_CLASS ((inst), G_TYPE_TLS_CONNECTION_GNUTLS, GTlsConnectionGnutlsClass))

typedef struct _GTlsConnectionGnutlsPrivate                   GTlsConnectionGnutlsPrivate;
typedef struct _GTlsConnectionGnutlsClass                     GTlsConnectionGnutlsClass;
typedef struct _GTlsConnectionGnutls                          GTlsConnectionGnutls;

struct _GTlsConnectionGnutlsClass
{
  GTlsConnectionClass parent_class;

  void     (*failed)           (GTlsConnectionGnutls  *gnutls);

  void     (*begin_handshake)  (GTlsConnectionGnutls  *gnutls);
  void     (*finish_handshake) (GTlsConnectionGnutls  *gnutls,
				GError               **inout_error);
};

struct _GTlsConnectionGnutls
{
  GTlsConnection parent_instance;
  GTlsConnectionGnutlsPrivate *priv;
};

GType g_tls_connection_gnutls_get_type (void) G_GNUC_CONST;

gnutls_certificate_credentials_t g_tls_connection_gnutls_get_credentials (GTlsConnectionGnutls *connection);
gnutls_session_t                 g_tls_connection_gnutls_get_session     (GTlsConnectionGnutls *connection);

void     g_tls_connection_gnutls_get_certificate     (GTlsConnectionGnutls  *gnutls,
						      gnutls_retr2_st       *st);

gboolean g_tls_connection_gnutls_request_certificate (GTlsConnectionGnutls  *gnutls,
						      GError               **error);

gssize   g_tls_connection_gnutls_read          (GTlsConnectionGnutls  *gnutls,
						void                  *buffer,
						gsize                  size,
						gboolean               blocking,
						GCancellable          *cancellable,
						GError               **error);
gssize   g_tls_connection_gnutls_write         (GTlsConnectionGnutls  *gnutls,
						const void            *buffer,
						gsize                  size,
						gboolean               blocking,
						GCancellable          *cancellable,
						GError               **error);

gboolean g_tls_connection_gnutls_check         (GTlsConnectionGnutls  *gnutls,
						GIOCondition           condition);
GSource *g_tls_connection_gnutls_create_source (GTlsConnectionGnutls  *gnutls,
						GIOCondition           condition,
						GCancellable          *cancellable);

typedef enum {
	G_TLS_DIRECTION_NONE = 0,
	G_TLS_DIRECTION_READ = 1 << 0,
	G_TLS_DIRECTION_WRITE = 1 << 1,
} GTlsDirection;

#define G_TLS_DIRECTION_BOTH (G_TLS_DIRECTION_READ | G_TLS_DIRECTION_WRITE)

gboolean g_tls_connection_gnutls_close_internal (GIOStream            *stream,
                                                 GTlsDirection         direction,
                                                 gint64                timeout,
                                                 GCancellable         *cancellable,
                                                 GError              **error);

G_END_DECLS

#endif /* __G_TLS_CONNECTION_GNUTLS_H___ */
