/* modulemd-linting.h
 *
 * Copyright (C) 2018 Red Hat, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef MODULEMD_LINTING_H
#define MODULEMD_LINTING_H

#include <glib.h>
#include <yaml.h>
#include "modulemd.h"
#include "private/modulemd-linting.h"

G_BEGIN_DECLS

void
mmd_lint_start (void);

void
mmd_lint_stop (void);

gboolean
mmd_lint_is_linting (void);

void
mmd_lint_problems_clear (void);

void
mmd_lint_log_problem_full (const yaml_event_t *event,
                           const gchar *doc_url,
                           const gchar *description,
                           ...);

G_END_DECLS

#endif /* MODULEMD_LINTING_H */
