/* modulemd-linting.c
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

#include <glib.h>
#include <string.h>
#include <yaml.h>
#include "modulemd.h"
#include "private/modulemd-linting.h"

/* private macros */

#define _RUN_IF_LINTING() \
  do {                    \
    if (! _linting)       \
      {                   \
        return;           \
      }                   \
  } while (0)

/* private types */

typedef struct _MMDLintProblem_s {
  yaml_event_t *event;
  gchar *doc_url;
  gchar *description;
} _MMDLintProblem;

/* file-level "private" globals */

static gboolean _linting = FALSE;
static GSList *_lint_problems = NULL;

/* private functions */

static _MMDLintProblem *
_mmd_lint_problem_new_full (const yaml_event_t *event, const gchar *doc_url,
                            const gchar *description)
{
  _MMDLintProblem *problem;

  g_return_val_if_fail (event != NULL || doc_url != NULL ||
                        description != NULL, NULL);

  problem = g_malloc0 (sizeof (_MMDLintProblem));

  if (event != NULL)
    {
      problem->event = g_malloc (sizeof (yaml_event_t));

      memcpy (problem->event, event, sizeof (yaml_event_t));
    }

  problem->doc_url = g_strdup (doc_url);
  problem->description = g_strdup (description);

  return problem;
}

static void
_mmd_lint_problem_free (_MMDLintProblem *problem)
{
  g_return_if_fail (problem != NULL);

  g_free (problem->event);
  g_free (problem->doc_url);
  g_free (problem->description);

  g_free (problem);
}

/* public functions */

void
mmd_lint_start (void)
{
  g_return_if_fail (! _linting);

  _linting = TRUE;
}

void
mmd_lint_stop (void)
{
  g_return_if_fail (_linting);

  _linting = FALSE;
}

gboolean
mmd_lint_is_linting (void)
{
  return _linting;
}

void
mmd_lint_problems_clear (void)
{
  g_slist_free_full (_lint_problems, (GDestroyNotify) _mmd_lint_problem_free);
  _lint_problems = NULL;
}

void
mmd_lint_log_problem (const yaml_event_t *event, const gchar *doc_url,
                      const gchar *description)
{
  _MMDLintProblem *problem;

  g_return_if_fail (event != NULL || doc_url != NULL || description != NULL);

  _RUN_IF_LINTING();

  problem = _mmd_lint_problem_new_full (event, doc_url, description);

  _lint_problems = g_slist_append (_lint_problems, problem);
}
