/* GIO - GLib Input, Output and Streaming Library
 *
 * Copyright 2010 Red Hat, Inc.
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

#ifndef __G_TLS_BACKEND_GNUTLS_H__
#define __G_TLS_BACKEND_GNUTLS_H__

#include <gio/gio.h>
#include <gnutls/gnutls.h>

G_BEGIN_DECLS

#define G_TYPE_TLS_BACKEND_GNUTLS            (g_tls_backend_gnutls_get_type ())
#define G_TLS_BACKEND_GNUTLS(inst)           (G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_TLS_BACKEND_GNUTLS, GTlsBackendGnutls))
#define G_TLS_BACKEND_GNUTLS_CLASS(class)    (G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_TLS_BACKEND_GNUTLS, GTlsBackendGnutlsClass))
#define G_IS_TLS_BACKEND_GNUTLS(inst)        (G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_TLS_BACKEND_GNUTLS))
#define G_IS_TLS_BACKEND_GNUTLS_CLASS(class) (G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_TLS_BACKEND_GNUTLS))
#define G_TLS_BACKEND_GNUTLS_GET_CLASS(inst) (G_TYPE_INSTANCE_GET_CLASS ((inst), G_TYPE_TLS_BACKEND_GNUTLS, GTlsBackendGnutlsClass))

typedef struct _GTlsBackendGnutls        GTlsBackendGnutls;
typedef struct _GTlsBackendGnutlsClass   GTlsBackendGnutlsClass;
typedef struct _GTlsBackendGnutlsPrivate GTlsBackendGnutlsPrivate;

struct _GTlsBackendGnutlsClass
{
  GObjectClass parent_class;

  GTlsDatabase*   (*create_database)      (GTlsBackendGnutls          *self,
                                           GError                    **error);
};

struct _GTlsBackendGnutls
{
  GObject parent_instance;
  GTlsBackendGnutlsPrivate *priv;
};

GType g_tls_backend_gnutls_get_type (void) G_GNUC_CONST;
void  g_tls_backend_gnutls_register (GIOModule *module);

void    g_tls_backend_gnutls_store_session  (unsigned int             type,
					     GBytes                  *session_id,
					     GBytes                  *session_data);
void    g_tls_backend_gnutls_remove_session (unsigned int             type,
					     GBytes                  *session_id);
GBytes *g_tls_backend_gnutls_lookup_session (unsigned int             type,
					     GBytes                  *session_id);

G_END_DECLS

#endif /* __G_TLS_BACKEND_GNUTLS_H___ */
