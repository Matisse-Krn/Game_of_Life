# 0.5.0 HUD — release acceptance checklist

This checklist is deliberately separate from automated tests. Do not tag a
release until the items below have been checked on the intended Linux/X11
target. Mark observed results in the release notes; do not assume that a
headless pass implies a functional GUI.

## Automated gate

- [ ] Start with a clean clone of the release branch; verify the intended
      MiniLibX and libft pinned revisions are downloaded.
- [ ] Run `make -j2` and confirm `./game_of_life` is produced, without compiler
      warnings or missing libraries.
- [ ] Run `make test`: world, HUD, input and camera suites must all pass.
- [ ] Confirm the Linux GitHub Actions workflow passes on the release commit.
- [ ] Run `git diff --check` and confirm the working tree contains no
      accidental generated files or dependency modifications.

## GUI and controls (real X11 session or XWayland)

- [ ] Launch from an interactive session. On a shell with no valid `DISPLAY`,
      verify startup fails cleanly with an error and without hanging.
- [ ] Observe initial cells and HUD. Confirm rendered cells are correctly
      aligned, text remains readable, and panels never corrupt the grid.
- [ ] Pause/resume (Space), advance one generation while paused (N), clear (C),
      reseed (R), change border wrapping (B), and hide/show HUD (H).
- [ ] Hold Space, B, C, R and H for several seconds with X11 key autorepeat
      enabled. Each physical key press/release must trigger at most one action.
- [ ] Repeat a short physical tap, followed by a fast double tap, to check that
      distinct user actions remain responsive.
- [ ] Hold two arrow keys simultaneously; test movement at minimum, medium
      and maximum zoom. Confirm the camera moves smoothly even at high zoom.
- [ ] Test keyboard zoom (+/-), mouse wheel zoom and mouse dragging. Ensure
      changing zoom does not cause unexpected jumps or stuck dragging.
- [ ] Test Page Up/Page Down speed changes and verify the TPS shown by the
      HUD reacts accordingly.
- [ ] While holding an arrow key or mouse drag, switch to another window and
      back. Input must not remain stuck after losing focus.
- [ ] Close the window with the window manager and quit using Esc. Both paths
      must terminate without crash or orphaned process.

## Window geometry and rendering

- [ ] Check a large screen (for example 1920 × 1080): current window limits
      cap the drawing area at 1920 × 1050.
- [ ] Check a medium-size desktop (for example 800 × 600): the help, status
      and mouse panels must remain within the framebuffer.
- [ ] Check a small X11 screen (for example 320 × 240): compact HUD behavior
      must remain safe; partial or omitted text is an accepted limitation.
- [ ] Check the smallest screen size that the target desktop actually allows.
      Verify mouse coordinates outside the world are reported as such.
- [ ] Observe camera movement near edges in bounded and toroidal modes, and
      rendering at both extreme zoom levels.
- [ ] Check both normal X11 and XWayland if both are supported release targets.

## Stability and performance

- [ ] Run for at least 15 minutes with a dense, changing world and the HUD
      visible. Watch CPU load, memory usage and responsiveness.
- [ ] Raise target TPS above the achieved frame rate. Confirm the UI stays
      interactive while stepping is capped to eight generations per frame.
- [ ] Suspend/resume the computer or pause the process briefly. Confirm the
      camera and simulation do not perform a very large catch-up jump.
- [ ] Use a memory checker (Valgrind or AddressSanitizer in a compatible
      runtime) to inspect application shutdown and startup failure paths.
- [ ] Confirm repeated app launches/exits do not leak a substantial amount
      of memory or leave the display connection active.

## Publish

- [ ] Address all defects classified as release blockers; record any accepted
      known limitations explicitly.
- [ ] Update version/release notes to distinguish the new HUD behavior from
      the last stable release.
- [ ] Commit and review the code, tests and documentation. Confirm that the
      release tag points to the reviewed commit.
- [ ] Verify the repository can be rebuilt from that exact tag on the stated
      supported Linux platform.
