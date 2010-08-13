<?php
// $Id$

/**
 * @file
 * Rules module integration.
 */

/**
 * Implementation of hook_rules_action_info().
 * @ingroup rules
 */
function node_expire_rules_action_info() {
  return array(
    'node_expire_unset_expired' => array(
      'arguments' => array(
        'node'      => array('type' => 'node', 'label' => t('content expired')),
      ),
      'label'     => t('Unset the expired flag'),
      'module'    => 'Node',
    ),
  );
}

/**
 * Implementation of hook_rules_condition_info().
 * @ingroup rules
 */
function node_expire_rules_condition_info() {
  return array(
    'node_expire_rules_expired_check' => array(
      'arguments' => array(
        'node'      => array('type' => 'node', 'label' => t('Content')),
      ),
      'label'     => t('Content is expired'),
      'help'      => 'Evaluates to TRUE, if the given content has one of the selected content types.',
      'module'    => 'Node',
    ),
  );
}

/**
 * Implementation of hook_rules_event_info().
 * @ingroup rules
 */
function node_expire_rules_event_info() {
  return array(
    'node_expired' => array(
      'arguments' => rules_events_node_arguments(t('content expired'), t("content's author")),
      'label'     => t('Content expired'),
      'module'    => 'Node',
    ),
  );
}

/**
 * Check if the node has the the "Expired" flag on.
 *
 * @param $node
 *   Object. The Node object.
 */
function node_expire_rules_expired_check($node) {
  return (!empty($node->expire) && $node->expire <= time() && $node->expired == 1);
}

/**
 * Set the "Expired" flag on nodes after they are called by Rules module
 *
 * @param $nids
 *   Array. An array list with all node IDs
 *   that should be change the expired flag to TRUE.
 */
function node_expire_set_expired($nids) {
  if ($nids) {
    db_query('UPDATE {node_expire} SET expired = 1 WHERE nid IN ('. implode(',', $nids) .')');
  }
}

/**
 * Unset the "Expired" flag on nodes.
 *
 * @param $nids
 *   Object. The Node object with all node IDs
 *   that should be changed the expired flag to FALSE.
 */
function node_expire_unset_expired($nids) {
  if ($nids->nid) {
    db_query("UPDATE {node_expire} SET expired = 0 WHERE nid = '" . $nids->nid . "'");
  }
}
