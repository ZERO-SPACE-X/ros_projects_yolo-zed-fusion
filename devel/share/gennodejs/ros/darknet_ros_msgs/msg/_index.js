
"use strict";

let BoundingBox = require('./BoundingBox.js');
let BoundingBoxes = require('./BoundingBoxes.js');
let ObjectCount = require('./ObjectCount.js');
let CheckForObjectsResult = require('./CheckForObjectsResult.js');
let CheckForObjectsActionFeedback = require('./CheckForObjectsActionFeedback.js');
let CheckForObjectsFeedback = require('./CheckForObjectsFeedback.js');
let CheckForObjectsAction = require('./CheckForObjectsAction.js');
let CheckForObjectsActionResult = require('./CheckForObjectsActionResult.js');
let CheckForObjectsGoal = require('./CheckForObjectsGoal.js');
let CheckForObjectsActionGoal = require('./CheckForObjectsActionGoal.js');

module.exports = {
  BoundingBox: BoundingBox,
  BoundingBoxes: BoundingBoxes,
  ObjectCount: ObjectCount,
  CheckForObjectsResult: CheckForObjectsResult,
  CheckForObjectsActionFeedback: CheckForObjectsActionFeedback,
  CheckForObjectsFeedback: CheckForObjectsFeedback,
  CheckForObjectsAction: CheckForObjectsAction,
  CheckForObjectsActionResult: CheckForObjectsActionResult,
  CheckForObjectsGoal: CheckForObjectsGoal,
  CheckForObjectsActionGoal: CheckForObjectsActionGoal,
};
